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
map<string, double*> Iris;

int main() {
    Iris["Iris-setosa"] = new double[3]{0,0,1};
    Iris["Iris-virginica"] = new double[3]{0,1,0};
    Iris["Iris-versicolor"] = new double[3]{1,0,0};
    string cadena;
    string deli = ",";
    ifstream fe("dataset/iris/iris.data");
    size_t pos = 0;
    string token;
    double auxd[150][4];
    string valor_aux[150];
    double datos[110][4];
    string valor[110];
    double test[40][4];
    string valor_test[40];
    double max[4] = {};
    double min[4] = {};
    for(int i = 0, k = 0; i < 150; i++, k = (k+7)%150){
        fe >> cadena;
        int j = 0;
        while ((pos = cadena.find(deli)) != std::string::npos) {
            token = cadena.substr(0, pos);
            double aux = atof(token.c_str());
            auxd[i][j] = aux;
            max[j] = aux > max[j] ? aux : max[j];
            min[j] = aux < min[j] ? aux : min[j];
//            cout << token << endl;
            cadena.erase(0, pos + deli.length());
            j++;
        }
        valor_aux[i] = cadena;

    }
    fe.close();


    for(int i = 0, k = 0; i < 150; i++, k = (k+7)%150){
        for(int j = 0; j < 4; j++){
            token = cadena.substr(0, pos);
            double aux = atof(token.c_str());
            if(i < 110)
                datos[i][j] = auxd[k][j];
            else
                test[i - 110][j] = auxd[k][j];
//            cout << token << endl;
        }
        if(i < 110)
            valor[i] = valor_aux[k];
        else
            valor_test[i - 110] = valor_aux[k];
    }
    for(int i = 0; i < 110; i++)
        for(int j = 0; j < 4; j++)
            datos[i][j] = (datos[i][j] - min[j])/(max[j] - min[j]);
    for(int i = 0; i < 40; i++)
        for(int j = 0; j < 4; j++)
            test[i][j] = (test[i][j] - min[j])/(max[j] - min[j]);
//    for(int i = 0; i < 100; i++)
//        cout << datos[i][0] << endl;

    auto *red = new RedNeuronal(4, new int[3]{10,10,10}, 3, new Funcion*[3]{new Tanh(), new Tanh(), new Tanh()} , 3);
    for(int j = 0; j < 100; j++)
        for(int i = 0; i < 110; i++){
            cout << "back " << i << endl;
            red->backPropagation(datos[i], Iris[valor[i]]);
        }
    for(int i = 0; i < 40; i++){
        double* res = red->forward(test[i]);
        cout << "-------------" << endl;
        cout << "IRIS:  " << valor_test[i] << endl;
        for(int k = 0; k < 4; k++)
            cout << "   attr " << k << "  " << test[i][k];
        for (int j = 0; j < 3 ; j++) {
            cout << endl;
            cout << "res " << res[j] << endl;
            cout << "real " << Iris[valor_test[i]][j] << endl;
        }
    }
//--------------------------------------------------

//--------------------------------------------------
    return 0;
}


