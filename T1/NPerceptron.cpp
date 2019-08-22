//
// Created by nikom on 14-08-2019.
//

#include "NPerceptron.h"

NPerceptron::NPerceptron(double* w, double bias, int n){
    this->w = w;
    this->bias = bias;
    this->n = n;
    this->x = nullptr;
}
NPerceptron::~NPerceptron()= default;

int NPerceptron::setW(double* w) {
    if((sizeof(w)/sizeof(*w)) - this->n > 0.001)
        return -1;
    this->w = w;
    return 0;
}
double* NPerceptron::getW() const{
    return this->w;
}
double* NPerceptron::getX() const{
    return this->x;
}

double NPerceptron::getBias() const{
    return this->bias;
}

int NPerceptron::feed(double *x){
    if( sizeof(x)/ sizeof(*x) - n < 0.000000001) {
        this->x = x;
        return 0;
    }
    return -1;
}
double NPerceptron::eval() const{
    if(this->x != nullptr){
        double aux = 0;
        for(int i = 0; i < this->n ; i++)
            aux += this->x[i]*this->w[i];
        if(aux + this->bias > 0)
            return 1;
        return 0;
    }
    throw std::logic_error("[NPerceptron] eval: invalid x");
}

int NPerceptron::setBias(double nbias) {
    this->bias = nbias;
    return 0;
}
