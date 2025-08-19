#include <memory>
#include <string>
#include <thread>
#include <iostream>
#include <mutex>
#include <condition_variable>

struct Fork {
    bool occupied = false;
    std::mutex mutex;
    std::condition_variable taken;

    void pickup(std::string_view philosopherName, std::string_view hand) {
        {
        std::unique_lock lock(mutex);
        taken.wait(lock, [&] {
            std::cout << philosopherName << " is waiting for " << hand << " hand fork" << std::endl;
            return !occupied;
        });
        std::cout << philosopherName << " is taking " << hand << " hand fork" << std::endl;

        occupied = true;
        }
    }

    void layDown(std::string_view philosopherName, std::string_view hand) {
        std::cout << philosopherName << " is releasing " << hand << " hand fork" << std::endl;
        occupied = false;
        taken.notify_all();
    }
};

class Philosopher {
private:
    std::string name;

    std::shared_ptr<Fork> rightFork;
    std::shared_ptr<Fork> leftFork;

public:
    Philosopher(std::string name) : name(name) {}

    std::shared_ptr<Fork> RightFork() const {
        return rightFork;
    }
    std::shared_ptr<Fork> &RightFork() {
        return rightFork;
    }

    std::shared_ptr<Fork> LeftFork() const {
        return leftFork;
    }
    std::shared_ptr<Fork> &LeftFork() {
        return leftFork;
    }

    void eat() {
        while(true) {
        leftFork->pickup(name, "left");
        if (rightFork->occupied) {
            leftFork->layDown(name, "left");
            continue;
        }
        rightFork->pickup(name, "right");

        // Simulating the Philosopher eating
        std::cout << name << " started eating" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout << name << " is done eating" << std::endl;

        leftFork->layDown(name, "left");

        rightFork->layDown(name, "right");
        }
    }
};

int main() {
    std::shared_ptr<Fork> fork1 = std::make_shared<Fork>();
    std::shared_ptr<Fork> fork2 = std::make_shared<Fork>();
    std::shared_ptr<Fork> fork3 = std::make_shared<Fork>();
    std::shared_ptr<Fork> fork4 = std::make_shared<Fork>();
    std::shared_ptr<Fork> fork5 = std::make_shared<Fork>();

    Philosopher Shrek("Shrek");
    Shrek.LeftFork() = fork1;
    Shrek.RightFork() = fork2;

    Philosopher Donkey("Donkey");
    Donkey.LeftFork() = fork2;
    Donkey.RightFork() = fork3;

    Philosopher Fiona("Fiona");
    Fiona.LeftFork() = fork3;
    Fiona.RightFork() = fork4;

    Philosopher Puss("Puss");
    Puss.LeftFork() = fork4;
    Puss.RightFork() = fork5;

    Philosopher Dragon("Dragon");
    Dragon.LeftFork() = fork5;
    Dragon.RightFork() = fork1;

    std::thread threadShrek([&](){Shrek.eat();});
    std::thread threadDonkey([&](){Donkey.eat();});
    std::thread threadFiona([&](){Fiona.eat();});
    std::thread threadPuss([&](){Puss.eat();});
    std::thread threadDragon([&](){Dragon.eat();});

    threadShrek.join();
    threadDonkey.join();
    threadFiona.join();
    threadPuss.join();
    threadDragon.join();

    return 0;
}