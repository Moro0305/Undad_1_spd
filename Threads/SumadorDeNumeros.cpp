//
// Created by root on 8/19/25.
//

#include "SumadorDeNumeros.h"

SumadorDeNumeros::SumadorDeNumeros() {
    generador.seed(std::chrono::high_resolution_clock::now().time_since_epoch().count());
}

int SumadorDeNumeros::sumarNumeros() {
    std::uniform_int_distribution<int> distribucion(1, 1000);
    int suma = 0;
    for (int i = 0; i < 100; ++i) {
        suma += distribucion(generador);
    }
    return suma;
}