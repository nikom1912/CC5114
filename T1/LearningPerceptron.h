//
// Created by nikom on 14-08-2019.
//

#ifndef C___LEARNINGPERCEPTRON_H
#define C___LEARNINGPERCEPTRON_H

#define LR 0.1
#include "NPerceptron.h"
#include "Funciones.h"

class LearningPerceptron : public NPerceptron {
protected:
    double delta;
    Funciones* func;
public:
    LearningPerceptron(double *ws, double bias, int n, Funciones* nfunc);
//    int train(double* inputs, double expected);
    void setDelta(double delta);
    double getDelta();
    double eval() const override;
    void train();
};


#endif //C___LEARNINGPERCEPTRON_H
