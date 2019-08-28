//
// Created by nikom on 21-08-2019.
//

#include "Funcion.h"
#include <iostream>

double Sigmoid::apply(double x) const{
    double aux = 1.0 + exp(-x);
    return 1.0/aux;
}

double Sigmoid::derivative(double x) const {
    double aux = this->apply(x);
    return aux*(1.0 - aux);
}

double Tanh::apply(double x) const {
    double t = tanh(x);
    return t;
}



double Tanh::derivative(double x) const {
    double t = this->apply(x);
//    std::cout << "tan " << x << "   " << 1 - pow(tan, 2) << std::endl;
    return 1.0 - pow(t, 2);
}

double Step::apply(double x) const {
    if(x >= 0)
        return 1;
    else
        return 0;
}

double Step::derivative(double x) const {
    return 0;
}