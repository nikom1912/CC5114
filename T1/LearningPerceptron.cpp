//
// Created by nikom on 14-08-2019.
//

#include "LearningPerceptron.h"


//int LearningPerceptron::train(double* inputs, double expected){
//    double lr = 0.1;
//    this->feed(inputs);
//    if(this->eval() == -1)
//        return -1;
//    double real = this->eval();
//    double  diff = expected -real;
//    double nw[this->n];
//    for(int i = 0; i < this->n ; i++)
//        nw[i] = lr*this->w[i]*diff;
//    double nBias = this->bias + lr*diff;
//    if(this->setW(nw) == -1)
//        return -1;
//    this->setBias(nBias);
//    return 0;
//}

LearningPerceptron::LearningPerceptron(double *ws, double bias, int n, Funciones* nfunc) : NPerceptron(ws, bias, n){
    this->delta = 0.0;
    this->func = nfunc;
}

void LearningPerceptron::setDelta(double ndelta) {
    this->delta = ndelta;
}

double LearningPerceptron::getDelta() {
    return delta;
}

void LearningPerceptron::train() {
    double* W = this->getW();
    double bias = this->getBias();
    for(int i = 0; i < this->n; i++)
        W[i] += LR*delta*this->x[i];
    bias += LR*delta;
    this->setW(W);
    this->setBias(bias);
}

double LearningPerceptron::eval() const {
    if(this->x != nullptr){
        double aux = 0;
        for(int i = 0; i < this->n ; i++)
            aux += this->x[i]*this->w[i];
        return this->func->apply(aux + bias);
    }
}
