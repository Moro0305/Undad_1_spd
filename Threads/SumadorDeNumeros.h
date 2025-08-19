//
// Created by root on 8/19/25.
//

#ifndef SUMADORDENUMEROS_H
#define SUMADORDENUMEROS_H

#include <random>
#include <chrono>

class SumadorDeNumeros {
private:
    std::mt19937 generador;

public:
    SumadorDeNumeros();
    int sumarNumeros();
};

#endif // SUMADORDENUMEROS_H