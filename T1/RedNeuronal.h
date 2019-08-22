//
// Created by nikom on 19-08-2019.
//

#ifndef REDES_NEURONALES_REDNEURONAL_H
#define REDES_NEURONALES_REDNEURONAL_H

#include "SigmoidNeuron.h"
#include "LearningPerceptron.h"
#include "Layer.h"
#include "Funciones.h"


class RedNeuronal {
private:
    int capas;
    int salidas;
    int entradas;
    Layer<LearningPerceptron>** layers;


public:
    RedNeuronal(int num_inputs, int *capas, int n, Funciones** func, int salidas);
    ~RedNeuronal();

    void backPropagation(double* expected);
    double* forward(double* inputs) const;
};


#endif //REDES_NEURONALES_REDNEURONAL_H