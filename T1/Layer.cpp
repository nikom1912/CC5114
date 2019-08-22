//
// Created by nikom on 19-08-2019.
//

#include "Layer.h"
#include <random>

template <class T>
void OutLayer<T>::train() {
    for(int i = 0; i < this->largo; i++)
        this->capa[i]->train();
}

template <class T>
HiddenLayer<T>::HiddenLayer(int entrada, int n, Funciones* nfunc): Layer<T>(entrada, n, nfunc) {
}

template <class T>
double* HiddenLayer<T>::backPropagation(double *arg) {
    double* outputs = this->evalLayer();
    double out_errores[this->entradas] = {};
    for(int i = 0; i < this->largo; i++){
        double delt = arg[i]*this->func->derivative(outputs[i]);
        this->get(i)->setDelta(delt);
        for(int j = 0; j < this->entradas; j++)
            out_errores[j] += this->get(i)->getW()[j]*delt;
    }
    return out_errores;
}

template <class T>
void HiddenLayer<T>::train() {
    for(int i = 0; i < this->largo; i++)
        this->capa[i]->train();
}

template <class T>
Layer<T>::Layer() {
    entradas = 0;
    largo = 0;
    func = new Sigmoid();
    capa = nullptr;
}

template <class T>
Layer<T>::Layer(int entrada, int n, Funciones *nfunc) {
    func = nfunc;
    largo = n;
    entradas = 0;
    capa= new T*[n];
    for(int i = 0; i < n; i++){
        auto *w = new double[entrada];
        for(int j = 0; j < entrada; j++){
            w[j] =((rand()%100)/10.0) - 5;
        }
        capa[i] = new T(w, 0, entrada, nfunc);
    }
}

template <class T>
Layer<T>::~Layer() = default;

template <class T>
T* Layer<T>::get(int n) const {
    if(n >= this->largo){
        throw std::logic_error("[LAYER] get: index out of bound");
    }
    return this->capa[n];
}

template <class T>
int Layer<T>::getLargo() const {
    return this->largo;
}

template <class T>
void Layer<T>::feedLayer(double* x) {
    for(int i = 0; i < this->largo; i++){
        this->capa[i]->feed(x);
    }
}

template <class T>
double* Layer<T>::evalLayer() const{
    auto *out = new double[largo];
    for(int i = 0; i < this->largo; i++){
        out[i] = this->capa[i]->eval();
    }
    return out;
}



