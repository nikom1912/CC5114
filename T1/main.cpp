#include <iostream>
#include <fstream>
#include "SigmoidNeuron.h"
#include "LearningPerceptron.h"
#include "Layer.h"
#include <cstring>
#include <map>
#include <stdlib.h>
using namespace std;


int main() {
    string cadena;
    string deli = ",";
    ifstream fe("dataset/iris/iris.data");
    size_t pos = 0;
    string token;
    double datos[100][4];
    string valor[100];
    double test[50][4];
    string valor_test[50];
    double max[4] = {};
    double min[4] = {};
    for(int i = 0; i < 100; i++) {
        fe >> cadena;
        int j = 0;
        while ((pos = cadena.find(deli)) != std::string::npos) {
            token = cadena.substr(0, pos);
            double aux = atof(token.c_str());
            datos[i][j] = aux;
            max[j] = aux > max[j] ? aux : max[j];
            min[j] = aux < min[j] ? aux : min[j];
//            cout << token << endl;
            cadena.erase(0, pos + deli.length());
            j++;
        }
        valor[i]= cadena;
    }
    for(int i = 0; i < 50; i++) {
        fe >> cadena;
        int j = 0;
        while ((pos = cadena.find(deli)) != std::string::npos) {
            token = cadena.substr(0, pos);
            double aux = atof(token.c_str());
            test[i][j] = aux;
            max[j] = aux > max[j] ? aux : max[j];
            min[j] = aux < min[j] ? aux : min[j];
//            cout << token << endl;
            cadena.erase(0, pos + deli.length());
            j++;
        }
        valor_test[i] = cadena;
    }
    for(int i = 0; i < 100; i++)
        for(int j = 0; j < 4; j++)
            datos[i][j] = (datos[i][j] - min[j])/(max[j] - min[j]);
    for(int i = 0; i < 50; i++)
        for(int j = 0; j < 4; j++)
            test[i][j] = (test[i][j] - min[j])/(max[j] - min[j]);
    fe.close();

    return 0;
}