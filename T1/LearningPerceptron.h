//
// Created by nikom on 14-08-2019.
//

#ifndef C___LEARNINGPERCEPTRON_H
#define C___LEARNINGPERCEPTRON_H

#include "NPerceptron.h"
#include "Funcion.h"

/*
 * Clase LearningPerceptron
 * NPerceptron con la capacidad de aprender
 */
class LearningPerceptron : public NPerceptron {
protected:
    // delta (error) del LearningPerceptron entre el output dado y su valor esperado
    double delta;
    //funcion de activacion
    Funcion *func;
    // learning rate
    double lr = 0.1;
public:
    /*
     * Constructor de LearningPerceptron
     * @param ws pesos asignados al perceptron
     * @param bias bias
     * @param n numero de inputs del perceptron
     * @paran nfunc funcion de activacion
     */
    LearningPerceptron(double *ws, double bias, int n, Funcion *nfunc);

    /*
    * Constructor de LearningPerceptron
    * @param ws pesos asignados al perceptron
    * @param bias bias
    * @param n numero de inputs del perceptron
    * @param nfunc funcion de activacion
    * @param lr learning rate
    */
    LearningPerceptron(double *ws, double bias, int n, Funcion *nfunc, double lr);
//    int train(double* inputs, double expected);
    /*
     * setter de delta
     * @param delta nuevo delta
     */
    void setDelta(double delta);
    /*
     * getter del delta
     * @return delta
     */
    double getDelta();
    /*
     * evalua los inputs del perceptron y retorna un valor output
     * @return valor de output del perceptron
     */
    double eval() const override;

    /*
     * Actualiza los pesos y bias del perceptron de acuerdo al delta actual
     */
    void train();

    /*
     * Imprime los pesos del perceptron
     */
    void disp() const;
};


#endif //C___LEARNINGPERCEPTRON_H
