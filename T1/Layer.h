//
// Created by nikom on 19-08-2019.
//

#ifndef REDES_NEURONALES_LAYER_H
#define REDES_NEURONALES_LAYER_H

#include "Funcion.h"
#include <iostream>


/*
 * Clase para una capa de "neuronas" tipo T de la red
 */
template <class T>
class Layer {
protected:
    // numero de inputs de la capa (neuronas que la componen)
    int entradas;

    // array de neuronas
    T** capa;

    // cantidad de neuronas de la capa
    int largo;

    //funcion de activacion para la capa
    Funcion *func;

public:
    /*
     * Constructor de un Layer
     * @param entrada numero de inputs de la capa
     * @param n cantidad de neuronas de la caoa
     * @param nfunc funcion de activacion
     */
    Layer(int entrada, int n, Funcion *nfunc);

    /*
     * Constructor de un Layer
     * @param entrada numero de inputs de la capa
     * @param n cantidad de neuronas de la caoa
     * @param nfunc funcion de activacion
     * @param lr learning rate
     */
    Layer(int entrada, int n, Funcion *nfunc, double lr);

    /*
     * Destructor de la capa
     */
    ~Layer();

    /*
     * Aplica la backpropagation en la capa
     */
    virtual double* backPropagation(double* arg) = 0;

    /*
     * obtiene la neurona en la posicion n
     * @param n indice de la neurona a obtener
     * @return neurona en la posicion n
     */
    T* get(int n) const;

    /*
     * Retorna el largo de la capa
     * @return largo
     */
    int getLargo() const;

    /*
     * Retorna el numero de inputs de la capa
     * @return entradas
     */
    int getEntrada() const;

    /*
     * alimenta cada neurona de la capa con inputs dados
     * @param x inputs
     */
    void feedLayer(double* x);

    /*
     * Evalua el output de cada neurona entregando un array con los outputs
     * @return array de outputs
     */
    double* evalLayer() const;

    /*
     * Actualiza los pesos de cada neurona en la capa
     */
    virtual void train() = 0;
    void disp();
};


/*
 * Clase para una capa de salida
 */
template <class T>
class OutLayer: public Layer<T> {
public:
    OutLayer(int entrada, int n);
    OutLayer(int entrada, int n, double lr);
    ~OutLayer() = default;
    double* backPropagation(double *arg);
    void train();
};

/*
 * Clase para una capa escondida o interna
 */
template <class T>
class HiddenLayer: public Layer<T>{
public:
    HiddenLayer(int entrada, int n, Funcion *nfunc);
    HiddenLayer(int entrada, int n, Funcion *nfunc, double lr);
    ~HiddenLayer() = default;
    double* backPropagation(double *arg);
    void train();
};

template <class T>
OutLayer<T>::OutLayer(int entrada, int n): Layer<T>(entrada, n, new Sigmoid()) {}

template <class T>
OutLayer<T>::OutLayer(int entrada, int n, double lr): Layer<T>(entrada, n, new Sigmoid(), lr) {}

template<class T>
double* OutLayer<T>::backPropagation(double *arg) {
    double* outputs = this->evalLayer();
    double error[this->largo] = {};
    auto *out_errores = new double[this->entradas];
    for(int i =0; i < this->largo; i++) {
        error[i] = arg[i] - outputs[i];
    }
    for(int i = 0; i < this->largo; i++){

        double delt = error[i]*(this->func->derivative(outputs[i]));
        this->capa[i]->setDelta(delt);
        for(int j = 0; j < this->entradas; j++) {
            out_errores[j] += this->get(i)->getW()[j] * delt;
        }
    }
    return out_errores;
}

template <class T>
void OutLayer<T>::train() {
    for(int i = 0; i < this->largo; i++)
        this->capa[i]->train();
}

template <class T>
HiddenLayer<T>::HiddenLayer(int entrada, int n, Funcion *nfunc): Layer<T>(entrada, n, nfunc) {
}

template <class T>
HiddenLayer<T>::HiddenLayer(int entrada, int n, Funcion *nfunc, double lr): Layer<T>(entrada, n, nfunc, lr) {
}

template <class T>
double* HiddenLayer<T>::backPropagation(double *arg) {
    double* outputs = this->evalLayer();
    auto *out_errores = new double[this->entradas];
    for(int i = 0; i < this->largo; i++){
        double delt = arg[i]*(this->func->derivative(outputs[i]));
        this->capa[i]->setDelta(delt);
        for(int j = 0; j < this->entradas; j++) {
            out_errores[j] += this->get(i)->getW()[j] * delt;
        }
    }
    return out_errores;
}

template <class T>
void HiddenLayer<T>::train() {
    for(int i = 0; i < this->largo; i++) {
        this->capa[i]->train();
    }
}


//Layer constructors
template <class T>
Layer<T>::Layer(int entrada, int n, Funcion *nfunc) {
    func = nfunc;
    largo = n;
    entradas = entrada;
    capa= new T*[n];
    for(int i = 0; i < n; i++){
        auto *w = new double[entrada];
        for(int j = 0; j < entrada; j++){
            w[j] =((double) rand()/RAND_MAX)*2 -1;
        }
        capa[i] = new T(w, 0, entrada, nfunc);
    }
}

template<class T>
Layer<T>::Layer(int entrada, int n, Funcion *nfunc, double lr) {
    func = nfunc;
    largo = n;
    entradas = entrada;
    capa= new T*[n];
    for(int i = 0; i < n; i++){
        auto *w = new double[entrada];
        for(int j = 0; j < entrada; j++)
            w[j] =((double) rand()/RAND_MAX)*3 - 1.5;
        capa[i] = new T(w, 0, entrada, nfunc, lr);
    }
}


//Layer destructor
template <class T>
Layer<T>::~Layer() = default;


/*
 *
 */
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

template <class T>
void Layer<T>::disp() {
    for(int i = 0; i < largo; i++)
        capa[i]->disp();
}

template <class T>
int Layer<T>::getEntrada() const {
    return  entradas;
}




#endif //REDES_NEURONALES_LAYER_H
