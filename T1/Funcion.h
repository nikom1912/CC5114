//
// Created by nikom on 21-08-2019.
//

#ifndef REDES_NEURONALES_FUNCION_H
#define REDES_NEURONALES_FUNCION_H

#include <cmath>
#include <iostream>
class Funcion {
public:
    virtual double apply(double x) const = 0;
    virtual double derivative(double x) const = 0;
};

class Sigmoid: public Funcion {
public:
    double apply(double x) const override;
    double derivative(double x) const override;
};

class Tanh: public Funcion {
public:
    double apply(double x) const override;
    double derivative(double x) const override;
};

class Step: public Funcion {
public:
    double apply(double x) const override;
    double derivative(double x) const override;
};



#endif //REDES_NEURONALES_FUNCION_H
