//
// Created by nikom on 14-08-2019.
//

#ifndef C___LEARNINGPERCEPTRON_H
#define C___LEARNINGPERCEPTRON_H

#define LR 0.1
#include "NPerceptron.h"
#include "Funcion.h"

class LearningPerceptron : public NPerceptron {
protected:
    double delta;
    Funcion *func;
public:
    LearningPerceptron(double *ws, double bias, int n, Funcion *nfunc);
//    int train(double* inputs, double expected);
    void setDelta(double delta);
    double getDelta();
    double eval() const override;
    void train();
    void disp() const;
};


#endif //C___LEARNINGPERCEPTRON_H
