//
// Created by nikom on 19-08-2019.
//

#include "RedNeuronal.h"
#include <cmath>

RedNeuronal::RedNeuronal(int num_inputs, int *capas, int n, Funciones** func,  int salidas) {
    this->layers = new Layer<LearningPerceptron>*[n + 1];
    this->layers[0] = new HiddenLayer<LearningPerceptron>(num_inputs, capas[0], func[0]);
    for(int i = 1; i < n; i++){
        this->layers[i] = new HiddenLayer<LearningPerceptron>(capas[i-1], capas[i], func[i]);
    }
    this->layers[n] = new OutLayer<LearningPerceptron>(capas[n-1], salidas);
    this->capas = n + 1;
    this->entradas = num_inputs;
    this->salidas = salidas;
}
RedNeuronal::~RedNeuronal() {
    delete this->layers;
}

double* RedNeuronal::forward(double *inputs) const {
    for(int i = 0; i < this->capas - 1; i++){
        this->layers[i]->feedLayer(inputs);
        inputs = this->layers[i]->evalLayer();
    }
    this->layers[capas - 1]->feedLayer(inputs);
    inputs = this->layers[capas - 1]->evalLayer();
    for(int j =  0; j < this->layers[capas - 1]->getLargo(); j++)
        inputs[j] = 1.0/(1 - std::exp(-inputs[j]));
    return inputs;
}

void RedNeuronal::backPropagation(double* expected) {
    double* error = this->layers[capas]->backPropagation(expected);
    for(int i = capas - 1; i >0; i--){
        error = this->layers[i]->backPropagation(error);
    }
    for(int i = 0; i < capas; i++)
        this->layers[i]->train();
}



