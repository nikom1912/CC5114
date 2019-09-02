//
// Created by nikom on 19-08-2019.
//

#ifndef REDES_NEURONALES_REDNEURONAL_H
#define REDES_NEURONALES_REDNEURONAL_H

#include "SigmoidNeuron.h"
#include "LearningPerceptron.h"
#include "Layer.h"
#include "Funcion.h"

/*
 * Clase para la red neuronal
 */
class RedNeuronal {
private:
    /*
     * numero de capas internas
     */
    int capas;

    /*
     * numero de outputs
     */
    int salidas;

    /*
     * numero de inputs
     */
    int entradas;

    /*
     * array de capas (Layer)
     */
    Layer<LearningPerceptron>** layers;


public:
    /*
     * Constructor de La red neuronal
     * @param num_inputs numero de inputs
     * @param *capas array de enteros que contiene la cantidad de neuronas por capa interna
     * @param n numero de capas internas
     * @param **func array de objetos de la clase Funcion para asignarse como funcion de activacion a cada capa
     * @param salidas numero de outputs y neuronas en la capa de salida
     */
    RedNeuronal(int num_inputs, int *capas, int n, Funcion** func, int salidas);

    /*
     * Constructor de La red neuronal
     * @param num_inputs numero de inputs
     * @param *capas array de enteros que contiene la cantidad de neuronas por capa interna
     * @param n numero de capas internas
     * @param **func array de objetos de la clase Funcion para asignarse como funcion de activacion a cada capa
     * @param salidas numero de outputs y neuronas en la capa de salida
     * @param lr learning rate
     */
    RedNeuronal(int num_inputs, int *capas, int n, Funcion** func, int salidas, double lr);

    //Destructor de la red
    ~RedNeuronal();

    /*
     * Computa Backpropagation y training de la red
     * @param *inputs array de inputs
     * @param expected array de los valores esperados para los inputs dados
     */
    void backPropagation(double* inputs, double* expected);

    /*
     * Evalua los inputs dados en la red para obtener un resultado
     * @param *inputs inputs a evaluar
     * @return respuesta de la red para los inputs
     */
    double* forward(double* inputs) const;

    void disp();
};


#endif //REDES_NEURONALES_REDNEURONAL_H
