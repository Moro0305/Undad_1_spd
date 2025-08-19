#include <iostream>
#include <vector>
#include <thread>
#include <future>
#include <algorithm>
#include "SumadorDeNumeros.h"

int main() {
    std::vector<std::thread> hilos;
    std::vector<std::future<int>> futuros;

    // Se crea una instancia de SumadorDeNumeros para cada hilo
    // para evitar problemas de concurrencia al usar el generador de números aleatorios
    std::vector<SumadorDeNumeros> sumadores(10);

    // Crear 10 hilos para sumar números
    for (int i = 0; i < 10; ++i) {
        std::promise<int> promesa;
        futuros.push_back(promesa.get_future());
        hilos.emplace_back([&sumadores, i, p = std::move(promesa)]() mutable {
            int resultado = sumadores[i].sumarNumeros();
            p.set_value(resultado);
        });
    }

    // Esperar a que todos los hilos terminen
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
        auto maxElemento = std::max_element(resultados.begin(), resultados.end());
        size_t indiceMax = std::distance(resultados.begin(), maxElemento);
        std::cout << "\nEl hilo con la puntuación más alta es el hilo " << indiceMax + 1 << " con una suma de: " << *maxElemento << std::endl;
    }

    return 0;
}