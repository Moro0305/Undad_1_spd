#include <iostream>
#include <vector>
#include <thread>
#include <future>
#include <algorithm>
#include <ranges>
#include "SumadorDeNumeros.h"

//Uso explicito de Threads
//Versión anterior manejaba hilos con la función async simpllificando la ejecicion en una linea

int main() {
    // Vector para almacenar los objetos thread
    std::vector<std::thread> hilos;

    // Vector para obtener los resultados de forma asíncrona
    std::vector<std::future<int>> futuros;

    // Crear una instancia de SumadorDeNumeros para cada hilo
    std::vector<SumadorDeNumeros> sumadores(10);

    // Crear 10 hilos explícitamente
    for (int i = 0; i < 10; ++i) {
        // Se crea un objeto promise para cada hilo
        std::promise<int> promesa;
        futuros.push_back(promesa.get_future());

        // El hilo ejecuta la función y guarda el resultado en la promesa
        hilos.emplace_back([&sumadores, i, p = std::move(promesa)]() mutable {
            int resultado = sumadores[i].sumarNumeros();
            p.set_value(resultado);
        });
    }

    // Esperar a que todos los hilos terminen su ejecución
    for (std::thread& hilo : hilos) {
        if (hilo.joinable()) {
            hilo.join();
        }
    }

    // Almacenar los resultados y mostrarlos
    std::vector<int> resultados;
    for (size_t i = 0; i < futuros.size(); ++i) {
        int resultado = futuros[i].get();
        resultados.push_back(resultado);
        std::cout << "El resultado del hilo " << i + 1 << " es: " << resultado << std::endl;
    }

    // Encontrar y mostrar el hilo con la puntuación más alta
    if (!resultados.empty()) {
        auto maxElemento = std::ranges::max_element(resultados);
        size_t indiceMax = std::distance(resultados.begin(), maxElemento);
        std::cout << "\nEl hilo con la puntuación más alta es el hilo " << indiceMax + 1 << " con una suma de: " << *maxElemento << std::endl;
    }

    return 0;
}
