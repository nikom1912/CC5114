#include <iostream>
#include "AddNode.h"
#include "MultNode.h"
#include <array>
#include <vector>
#include <random>


#include "AST.h"
#include "NodeFactory.h"
#include "GP.h"
#include <ctime>
#include <cstdlib>
#include <random>
#include <fstream>


int numToFind = 65346;
int population_size = 100;
double mutation_rate = 0.1;

int depth = 10;


AST<int>* ast;

//std::random_device rd;
//std::mt19937 gen(rd());


//funciones

/*
 * entrega el fitness de un individuo
 * @param resp lista de caracteristicas del individuo
 * @param number_char cantidad de caracteristicas (caracteres)
 * @return fitness
 * */
template <typename T>
int fitness(Node<T>* resp);

/*
 * genera un individuo (frase)
 * @param number_char cantidad de caracteristicas (caracteres)
 * @return array de caracteristicas del individuo generado
 */
template <typename T>
Node<T>* AST_factory(int d);

/*
 * genera el valor de un gen de un individuo (letras minusculas, mayusculas o espacio)
 * @return valor del gen
 */
//char gen_generator();

/*
 * muta algun gen del individuo
 * @param res individuo a mutar
 * @param number_char cantidad de caracteristicas de un individuo (caracteres)
 * @return individuo mutado
 */
template<typename T>
void mutate(Node<T>* n);

/*
 * crea una poblacion inicial aleatoria
 * @param population cantidad de individuos a crear
 * @param number_char cantidad de caracteristicas de un individuo (caracteres)
 * @return poblacion inicial
 */
template <typename T>
Node<T>** init_pop(int population);

/*
 * crea un nuevo individuo a partir de 2 padres
 * @param parent1 padre 1
 * @param parent2 padre 2
 * @param number_char cantidad de caracteristicas de un individuo (caracteres)
 *
 *@return individuo creado
 */
template <typename T>
Node<T>* generate_child(Node<T>* parent1, Node<T>* parent2);

/*
 * obtiene un indice random a partir de un fitness acumulado (ruleta)
 * @param acc_fitness lista de fitness acumulado
 * @param n largo de la lista de fitness
 * @return indice
 */
int getRandomIndex(int* acc_fitness, int n);

/*
 * Realiza la seleccion de los individuos que participaran en el crossover
 * @param population_res poblacion de la cual se seleccionara
 * @param acc_fitness lista de fitness acumulado
 * @param population cantidad de individuos en la poblacion
 * @return array de individuos seleccionados
 */
template <typename T>
Node<T>** seleccion(Node<T>** population_res, int* acc_fitness, int population);


int** shuffle(int** list, int n);

template <typename T>
int* get_fitness(Node<T>** resp, int population);

template <typename T>
bool termination(Node<T>* res);

/*
 * Obtiene el fitness acumulativo de una lista de fitnes ordenados
 * @param ordered_fitness lista de fitnes oredenada de menor a mayor
 * @param n tamaño de la lista de fitness
 * @return array de fitness acumulativo
 */
int* get_acc_fitness(int* ordered_fitness, int n);

int main() {
    auto functions = new std::vector<NodeFactory<int>*>();
    functions->push_back(new NodeFactory<int>(1));
    functions->push_back(new NodeFactory<int>(2));
    functions->push_back(new NodeFactory<int>(3));
    functions->push_back(new NodeFactory<int>(4));

    auto allowed = new std::vector<int>();
    allowed->push_back(25);
    allowed->push_back(7);
    allowed->push_back(8);
    allowed->push_back(100);
    allowed->push_back(4);
    allowed->push_back(2);


    ast = new AST<int>(functions, allowed, 0.2);

    srand(time(nullptr));
    auto *ga = new GP<Node<int>*>(population_size, mutation_rate, fitness, generate_child, get_fitness, init_pop,
                              AST_factory, termination,
                              mutate, seleccion,get_acc_fitness , 10000);

//    for (int i = 0; i <50 ; ++i) {
//        std::cout << rand()%(-1000) << std::endl;
//    }
    ga->run();
    std::vector<int> forGraph = ga->getListBestFitness();
    int iters = ga->getIters();
    std::ofstream file("r1.txt");
    file << "Grafico para encontrar numero: '" << numToFind << "'" << std::endl;
    file << population_size << std::endl;
    file << mutation_rate << std::endl;
    for(int i = 0; i < iters + 1; i++){
        file << forGraph[i] << "\n";
    }
    file.close();

}

template <class T>
int fitness(Node<T>* resp){
    return abs(numToFind - resp->eval());
}

template<class T>
Node<T>** init_pop(int population){
    auto pop  = new Node<T>*[population];
    for(int i = 0; i < population; i++){
        Node<T>* as = ast->create_rec_tree(depth);
        pop[i] = as;
    }
    return pop;
}

//char gen_generator(){
//    //caracteres codigo ascii [A-Z]= [65-90]   [a-z]=[97-122]  espacio=32
//    int r = 65 + std::rand()%27;
//
//    // espacio
//    if(r == 91)
//        return char(32);
//    int r2 = std::rand()%2;
//
//    //minusculas
//    if(r2 == 1)
//        r += 32;
//    return char(r);
//
//
//}

template<typename T>
void mutate(Node<T> *n){
    int k = n->countNodes();
    std::vector<Node<T>*>* ar = n->serialize();
    int aux_depth = rand()%10;
    Node<T>* node = ar->at(rand()%k);
    node->replace(ast->create_rec_tree(aux_depth));
}

template <typename T>
Node<T>* generate_child(Node<T>* parent1, Node<T>* parent2){
    auto new_element = parent1->copy();
    int n1 = new_element->countNodes();
    parent1->print();
    new_element->print();
    auto arr1 = new_element->serialize();
    auto p1 = arr1->at(rand()%n1);
    int n2 = parent2->countNodes();
    auto arr2 = parent2->serialize();
    auto p2 = arr2->at(rand()%n2);

    p1->replace(p2);
//    if((rand()%100)/100.0 < mutation_rate){
//        mutate(&new_element);
//    }

    return new_element;
}

int getRandomIndex(int *acc_fitness, int n){
    int sum_total = acc_fitness[n-1];
    std::uniform_int_distribution<unsigned long long> dis(0, sum_total);
    int r = dis(gen);
    for(int i = 0; i < n; i++){
        if(r <= acc_fitness[i]) {
            return i;
        }
    }
    return n - 1;
}

template <typename T>
Node<T>* AST_factory(int d){
    return ast->create_rec_tree(d);
}

template <typename T>
bool termination(Node<T>* res){
    return (res->eval() - numToFind) == 0;
}

template <typename T>
int* get_fitness(Node<T>** resp, int population){
    int* fitness_arr = new int[population];
    for(int i = 0; i < population; i++)
        fitness_arr[i] = fitness(resp[i]);
//    quicksort(fitness, 0, population);
    return fitness_arr;
}

template <typename T>
Node<T>** seleccion(Node<T>** population_res, int* acc_fitness , int population){
    auto selected = new Node<T>* [population];
    for(int i = 0; i < population; i++){
        int index = getRandomIndex(acc_fitness, population);
        selected[i] = population_res[index]->copy();
    }

    return selected;

}

int* get_acc_fitness(int* ordered_fitness, int n){
    int acc = 0;
    int* acc_fitness = new int[n];
    for(int i = 0; i < n; i++){
        acc += ordered_fitness[i];
        acc_fitness[i] = acc;
    }
    return acc_fitness;
}