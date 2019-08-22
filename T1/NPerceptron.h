//
// Created by nikom on 14-08-2019.
//
#include <iostream>
#include <stdexcept>
#ifndef C_NPERCEPTRON_H
#define C_NPERCEPTRON_H


class NPerceptron {
protected:
    int n;
    double *w;
    double *x;
    double bias;
public:
    NPerceptron(double* ws, double bias, int n);
    ~NPerceptron();

    int setW(double * w);
    int setBias(double nbias);

    double* getW() const;
    double* getX() const;
    double getBias() const;
    int feed(double *x);

    virtual double eval() const;

};


#endif //C_NPERCEPTRON_H
