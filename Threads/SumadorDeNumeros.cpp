#include "SumadorDeNumeros.h"

SumadorDeNumeros::SumadorDeNumeros() :
    generador(std::chrono::high_resolution_clock::now().time_since_epoch().count()) {
    // La inicialización se hace en la lista de inicialización del constructor.
}

int SumadorDeNumeros::sumarNumeros() {
    std::uniform_int_distribution<int> distribucion(1, 1000);
    int suma = 0;
    for (int i = 0; i < 100; ++i) {
        suma += distribucion(generador);
    }
    return suma;
}