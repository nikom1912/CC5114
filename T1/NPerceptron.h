//
// Created by nikom on 14-08-2019.
//
#include <iostream>
#include <stdexcept>
#ifndef C_NPERCEPTRON_H
#define C_NPERCEPTRON_H

/*
 * Clase que representa un perceptron con numero de inputs variables
 */
class NPerceptron {
protected:
    // numero de inputs
    int n;

    // pesos del perceptron
    double *w;

    // inputs del perceptron
    double *x;

    //bias
    double bias;
public:
    /*
     * Constructor de NPerceptron
     * @param ws pesos a asignar
     * @param bias bias
     * @param n numero de inputs(pesos)
     */
    NPerceptron(double* ws, double bias, int n);

    /*
     * destructor de NPerceptron
     */
    ~NPerceptron();

    /*
     * setter de w
     * @param w nuevos pesos
     */
    int setW(double * w);

    /*
     * Setter de bias
     * @param nbias nuevo bias
     */
    int setBias(double nbias);

    /*
     * getter de w
     * @return ws
     */
    double* getW() const;

    /*
     * getter de inputs x
     * @return x
     */
    double* getX() const;

    /*
     * getter de bias
     * @return bias
     */
    double getBias() const;

    /*
     * "Alimenta" al perceptron asignandole estableciendo valores de inputs y guardandolos en x
     * @param x inputs del perceptron
     */
    int feed(double *x);

    /*
     * Evalua el perceptro con los inputs guardados en x
     */
    virtual double eval() const;

};


#endif //C_NPERCEPTRON_H
