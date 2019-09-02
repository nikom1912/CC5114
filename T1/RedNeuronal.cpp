//
// Created by nikom on 19-08-2019.
//

#include "RedNeuronal.h"
#include <cmath>

RedNeuronal::RedNeuronal(int num_inputs, int *capas, int n, Funcion** func, int salidas) {
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

RedNeuronal::RedNeuronal(int num_inputs, int *capas, int n, Funcion** func, int salidas, double lr) {
    this->layers = new Layer<LearningPerceptron>*[n + 1];
    this->layers[0] = new HiddenLayer<LearningPerceptron>(num_inputs, capas[0], func[0], lr);
    for(int i = 1; i < n; i++){
        this->layers[i] = new HiddenLayer<LearningPerceptron>(capas[i-1], capas[i], func[i], lr);
    }
    this->layers[n] = new OutLayer<LearningPerceptron>(capas[n-1], salidas, lr);
    this->capas = n + 1;
    this->entradas = num_inputs;
    this->salidas = salidas;
}
RedNeuronal::~RedNeuronal() {
    delete this->layers;
}

double* RedNeuronal::forward(double *inputs) const {
    this->layers[0]->feedLayer(inputs);
    double *out = this->layers[0]->evalLayer();
    for(int i = 1; i < this->capas - 1; i++){
        this->layers[i]->feedLayer(out);
        out = this->layers[i]->evalLayer();
        delete[] out;
    }
    this->layers[capas - 1]->feedLayer(inputs);
    return this->layers[capas - 1]->evalLayer();
}

void RedNeuronal::backPropagation(double* inputs, double* expected) {
    this->forward(inputs);

    double* error = this->layers[capas - 1]->backPropagation(expected);
    for(int i = capas - 2; i >= 0; i--){
        error = this->layers[i]->backPropagation(error);
    }
    for(int i = 0; i < capas; i++) {
        this->layers[i]->train();
    }
}

void RedNeuronal::disp() {
    for(int i = 0; i < capas; i++){
        layers[i]->disp();
    }
}



