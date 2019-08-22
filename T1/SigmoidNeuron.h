//
// Created by nikom on 14-08-2019.
//

#ifndef C___SIGMOIDNEURON_H
#define C___SIGMOIDNEURON_H

#include "LearningPerceptron.h"
class SigmoidNeuron : public LearningPerceptron {
public:
    SigmoidNeuron(double* ws, double bias, int n);
    double eval() const;

};


#endif //C___SIGMOIDNEURON_H
