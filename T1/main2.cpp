//
// Created by nikom on 27-08-2019.
//
#include <iostream>
#include <fstream>
#include "SigmoidNeuron.h"
#include "LearningPerceptron.h"
#include "Layer.h"
#include "RedNeuronal.h"
#include <cstring>
#include <map>
#include <iterator>
#include <cstdlib>

using namespace std;

int main(){
    auto **func = new Funcion*[3]{new Sigmoid(), new Tanh(), new Tanh()};

    cout << func[0]->apply(3) << endl;
    cout << exp(-3) << endl;
    cout << func[0]->derivative(3) << endl;
    auto * l = new LearningPerceptron(new double[3]{0.1,0.2, 0.3}, 1, 3, new Tanh());
    l->feed(new double[3]{1,1,1});
    cout << l->eval() << endl;
    return 0;
}
