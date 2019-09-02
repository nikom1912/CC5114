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

void iris_red();
int argmax(double* l, int n);
void poker_red(int* capas_red, int n, Funcion** funciones, double lr);
void sensorial(int* capas_red, int n, Funcion** funciones, double lr);
int file_length(string filename);

int main() {
//    iris_red();
    sensorial(new int[3]{10,15, 12}, 3, new Funcion*[3]{new Tanh(), new Sigmoid(), new Sigmoid()}, 0.1);
    return 0;
}
void iris_red(){
    map<string, double*> Iris;
    Iris["Iris-setosa"] = new double[3]{0,0,1};
    Iris["Iris-virginica"] = new double[3]{1,0,0};
    Iris["Iris-versicolor"] = new double[3]{0,0,1};
    string cadena;
    int num_data = 140;
    int num_test = 150 - num_data;
    string deli = ",";
    ifstream fe("dataset/iris/iris.data");
    size_t pos = 0;
    string token;
    double auxd[150][4];
    string valor_aux[150];
    double datos[num_data][4];
    string valor[num_data];
    double test[num_test][4];
    string valor_test[num_test];
    double max[4] = {};
    double min[4] = {};

    for(int i = 0; i < 150; i++){
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


    for(int i = 0, k = 0; i < 150; i++, k = (k+13)%150){
        for(int j = 0; j < 4; j++){
            token = cadena.substr(0, pos);
            double aux = atof(token.c_str());
            if(i < num_data)
                datos[i][j] = auxd[k][j];
            else
                test[i - num_data][j] = auxd[k][j];
//            cout << token << endl;
        }
        if(i < num_data)
            valor[i] = valor_aux[k];
        else
            valor_test[i - num_data] = valor_aux[k];
    }
    for(int i = 0; i < num_data; i++)
        for(int j = 0; j < 4; j++)
            datos[i][j] = (datos[i][j] - min[j])/(max[j] - min[j]);
    for(int i = 0; i < num_test; i++)
        for(int j = 0; j < 4; j++)
            test[i][j] = (test[i][j] - min[j])/(max[j] - min[j]);
//    for(int i = 0; i < 100; i++)
//        cout << datos[i][0] << endl;

    auto *red = new RedNeuronal(4, new int[3]{25,25,25}, 3, new Funcion*[3]{new Sigmoid(), new Tanh(), new Sigmoid()} , 3);
    for(int j = 0; j < 1; j++)
        for(int i = 0; i < num_data; i++){
            cout << "back " << i << endl;
            red->backPropagation(datos[i], Iris[valor[i]]);
        }
    for(int i = 0; i <  num_test; i++){
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

    delete red;
}

void poker_red(int* capas_red, int n, Funcion** funciones, double lr = 0.1){
    map<int, double*> pokerMap;
    double* value;
    for(int i = 0; i < 10; i++) {
        value = new double[10]{};
        value[i] = 1;
        pokerMap[i] = value;
    }
    for(int i = 0; i < 10 ; i++ )
        cout << pokerMap[2][i] << endl;
    string cadena;
    string deli = ",";
    ifstream ftraining("dataset/poker/testing.data");
    ifstream ftest("dataset/poker/training.data");
    size_t pos = 0;
    string token;
    int num_data = 23000;
    int num_test = 30;
    double datos[num_data][10];
    int valor[num_data];
    double test[200][10];
    int valor_test[200];
    double max[10] = {};
    double min[10] = {};

    for(int i = 0; i < num_data; i++){
        ftraining >> cadena;
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
        valor[i] = stoi(cadena);
    }
    ftraining.close();
    int step = 13;
    for(int i = 0, k = 1 ; i < 200; i++){
        ftest >> cadena;
        int j = 0;
        while ((pos = cadena.find(deli)) != std::string::npos) {
            token = cadena.substr(0, pos);
            double aux = atof(token.c_str());
            test[i][j] = aux;
//            cout << token << endl;
            cadena.erase(0, pos + deli.length());
            j++;
        }
        valor_test[i] = stoi(cadena);
    }
    ftest.close();
    for(int i = 0; i < num_data; i++)
        for(int j = 0; j < 10; j++)
            datos[i][j] = (datos[i][j] - min[j])/(max[j] - min[j]);
    for(int i = 0; i < 200; i++)
        for(int j = 0; j < 10; j++)
            test[i][j] = (test[i][j] - min[j])/(max[j] - min[j]);
//    for(int i = 0; i < 100; i++)
//        cout << datos[i][0] << endl;


    for(int j = num_data; j <= num_data; j+= 50 ) {
        auto *red = new RedNeuronal(10, capas_red, n, funciones , 10 , lr);
        for (int i = 0; i < j; i++) {
            red->backPropagation(datos[i], pokerMap[valor[i]]);
        }
        for (int i = 50; i < 70; i++) {
            cout << "-------------------------------" << endl;
            double *res = red->forward(test[i]);
            cout << "Valor real: " << valor_test[i] << endl;
            for(int j = 0; j < 10; j++)
                cout << "Valor Obtenido:" << j << "  " << res[j] << endl;
            cout << "=====================================" << endl;
        }
        cout << "+++++++++++++++++++ " << j <<  "  +++++++++++++++++" << endl;
        delete red;
    }
}

void sensorial(int* capas_red, int n, Funcion** funciones, double lr = 0.1) {
    map<int, double*> sensorMap;
    double *value;
    int atrib = 48;
    int num_res = 11;
    for (int i = 1; i <= num_res; i++) {
        value = new double[num_res]{};
        value[i-1] = 1;
        sensorMap[i] = value;
    }
    string cadena;
    string deli = ",";
    size_t pos = 0;
    string token;
//    int num = file_length("dataset/sensorial/sensorial.txt") - 1;
    int num = file_length("dataset/sensorial/sensorial.txt") - 1;
    cout << num << endl;
    ifstream file("dataset/sensorial/sensorial.txt");
    auto **datos = new double*[num]{};
    for(int i = 0;i < num; i++)
        datos[i] = new double[48]{};
    int *valor = new int[num]{};
    auto **test = new double*[220]{};
    for(int i = 0; i < 220; i++)
        test[i] = new double[48]{};
    int valor_test[220];
    auto *max = new double[48]{};
    auto *min = new double[48]{};
    for(int i = 0; i < num; i++){
        file >> cadena;
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
        valor[i] = stoi(cadena);
    }
    file.close();
    for(int i = 0; i < num; i++)
        for(int j = 0; j < atrib; j++)
            datos[i][j] = (datos[i][j] - min[j])/(max[j] - min[j]);

    for(int i = 0; i < 220; i++){
        for(int j = 0; j < atrib; j++) {
            test[i][j] = datos[i * num / 220][j];
            valor_test[i] = valor[i * num / 220];
        }
    }

    for(int j = 0; j <= num; j+= 50) {
        auto *red = new RedNeuronal(48, capas_red, n, funciones , 11 , lr);
        for (int i = 0, k = 0; i < j; i++, k = k + num/j) {
            red->backPropagation(datos[k], sensorMap[valor[k]]);
        }
//        red->disp();
        for (int i = 0; i < 220; i++) {
            cout << "-------------------------------" << endl;
            double *res = red->forward(test[i]);
            cout << "Valor real"<< i <<": " << valor_test[i] << endl;
            cout << "Valor Obtenido:" << argmax(res, num_res) + 1 << endl;
            for(int j = 0; j < num_res; j++)
                cout << res[j] << "\t";
            cout << endl;
        }
        cout << "+++++++++++++++++++ " << j <<  "  +++++++++++++++++" << endl;
        delete red;
    }
    delete[] min;
    delete[] max;
}
int argmax(double* l, int n){
    double max = -1;
    int pos = -1;
    for(int i = 0; i < n ; i++){
        if(l[i] > max) {
            max = l[i];
            pos = i;
        }
    }
    return pos;
}

int file_length(string filename){
    ifstream file(filename);
    int largo = 0;
    string cadena;
    while(!file.eof()) {
        file >> cadena;
        largo++;
    }
    file.close();
    return largo;
}