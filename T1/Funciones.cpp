//
// Created by nikom on 21-08-2019.
//

#include "Funciones.h"

double Sigmoid::apply(double x) {
    return 1.0/(1 - exp(-x));
}

double Sigmoid::derivative(double x) {
    double aux = Sigmoid::apply(x);
    return aux*(1 - aux);
}

double Tanh::apply(double x) {
    return tanh(x);
}

double Tanh::derivative(double x) {
    return 1/pow(cosh(x), 2);
}
