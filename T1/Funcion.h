//
// Created by nikom on 21-08-2019.
//

#ifndef REDES_NEURONALES_FUNCION_H
#define REDES_NEURONALES_FUNCION_H

#include <cmath>
#include <iostream>

/*
 * Funciones de activacion para red neuronal
 */
class Funcion {
public:
    /*
     * @param x valor al que aplicar la funcion
     * @return valor resultante de la aplicacion de la funcion x
     */
    virtual double apply(double x) const = 0;

    /*
     * @param x valor al que aplicar la derivada la funcion
     * @return valor resultante de la aplicacion de la derivada de la funcion a x
     */
    virtual double derivative(double x) const = 0;
};

// Funcion sigmoide
class Sigmoid: public Funcion {
public:
    double apply(double x) const override;
    double derivative(double x) const override;
};


// funcion Tangente hiperbolica
class Tanh: public Funcion {
public:
    double apply(double x) const override;
    double derivative(double x) const override;
};

// funcion step
class Step: public Funcion {
public:
    double apply(double x) const override;
    double derivative(double x) const override;
};



#endif //REDES_NEURONALES_FUNCION_H
