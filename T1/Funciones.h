//
// Created by nikom on 21-08-2019.
//

#ifndef REDES_NEURONALES_FUNCIONES_H
#define REDES_NEURONALES_FUNCIONES_H

#include <cmath>

class Funciones {
public:
    virtual double apply(double x) = 0;
    virtual double derivative(double x) = 0;
};

class Sigmoid: public Funciones {
public:
    double apply(double x) override;
    double derivative(double x) override;
};

class Tanh: public Funciones {
public:
    double apply(double x) override;
    double derivative(double x) override;
};

//class Step: public Funciones {
//public:
//};



#endif //REDES_NEURONALES_FUNCIONES_H
