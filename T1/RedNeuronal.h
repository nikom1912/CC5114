//
// Created by nikom on 19-08-2019.
//

#ifndef REDES_NEURONALES_REDNEURONAL_H
#define REDES_NEURONALES_REDNEURONAL_H

#include "SigmoidNeuron.h"
#include "LearningPerceptron.h"
#include "Layer.h"
#include "Funcion.h"


class RedNeuronal {
private:
    int capas;
    int salidas;
    int entradas;
    Layer<LearningPerceptron>** layers;


public:
    RedNeuronal(int num_inputs, int *capas, int n, Funcion** func, int salidas);
    RedNeuronal(int num_inputs, int *capas, int n, Funcion** func, int salidas, double lr);
    ~RedNeuronal();

    void backPropagation(double* inputs, double* expected);
    double* forward(double* inputs) const;
    void disp();
};


#endif //REDES_NEURONALES_REDNEURONAL_H
