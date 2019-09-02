//
// Created by nikom on 14-08-2019.
//

#include "LearningPerceptron.h"

#include <utility>


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

LearningPerceptron::LearningPerceptron(double *ws, double bias, int n, Funcion *nfunc) : NPerceptron(ws, bias, n){
    this->delta = 0.0;
    this->func = nfunc;
}

LearningPerceptron::LearningPerceptron(double *ws, double bias, int n, Funcion *nfunc, double lr) : NPerceptron(ws, bias, n){
    this->delta = 0.0;
    this->func = nfunc;
    this->lr = lr;
}
void LearningPerceptron::setDelta(double ndelta) {
    this->delta = ndelta;
}

double LearningPerceptron::getDelta() {
    return delta;
}

void LearningPerceptron::train() {
    for(int i = 0; i < this->n; i++) {
        w[i] += lr * delta * this->x[i];
    }
    bias += lr*delta;
}

double LearningPerceptron::eval() const {
    double aux = 0;
    for(int i = 0; i < this->n ; i++)
        aux += this->x[i]*this->w[i];
    return this->func->apply(aux + bias);

}

void LearningPerceptron::disp() const {
    for(int i = 0; i < n; i++){
        std::cout << w[i] << "\t";
    }
    std::cout << std::endl;
}


