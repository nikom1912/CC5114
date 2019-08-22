//
// Created by nikom on 14-08-2019.
//

#include "SigmoidNeuron.h"
#include <cmath>

SigmoidNeuron::SigmoidNeuron(double *ws, double bias, int n) : LearningPerceptron(ws, bias, n, new Sigmoid()) {}

double SigmoidNeuron::eval() const {
    if(this->x != nullptr){
        double aux = 0;
        for(int i = 0; i < this->n ; i++)
            aux += this->x[i]*this->w[i];
        return 1.0/(1 + std::exp(-aux - this->bias));
    }
    throw std::logic_error("[NPerceptron] eval: invalid x");
}

