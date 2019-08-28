//
// Created by nikom on 21-08-2019.
//

#include "Funciones.h"
#include <iostream>

double Sigmoid::apply(double x) const{
    double aux = 1.0 - exp(-x);
    return 1.0/aux;
}

double Sigmoid::derivative(double x) {
    double aux = this->apply(x);
    return aux*(1.0 - aux);
}

double Tanh::apply(double x) const {
    double t = tanh(x);
    return t;
}

double Tanh::derivative(double x) {
    double t = this->apply(x);
//    std::cout << "tan " << x << "   " << 1 - pow(tan, 2) << std::endl;
    return 1.0 - pow(t, 2);
}
