//
// Created by nikom on 08-10-2019.
//

#ifndef T2_INTEGER_GA_H
#define T2_INTEGER_GA_H

#include "utils.h"
#include <string>
#include <iostream>

/*
 * clase para algoritmo genetico con atributos enteros y de cantidad fija
 */

class Integer_GA {
private:
    //numero de individuos por generacion
    int pop_size;
    //probabilidad de existencia de una mutacion
    double mutation_rate;

    //funcion para obtener la poblacion inicial
    int **(*init_pop)(int, int);

    //funcion para obtener el fitness de un individuo
    int (*fitness)(int *, int);

    //funcion que genera un individuo con atributos random
    int *(*individual_generator)(int);

    //funcion que retorna un valor para un gen
    int (*gen_generator)();

    // funcion para obtener los individuos seleccion y que posteriormente generaran (crossover) la nueva generacion
    int **(*selection)(int **, int *, int);

    //muta un gen de un individuo
    int* (*mutate)(int*, int);

    //retorna true si se cumple alguna condicion para parar el algoritmo
    bool (*termination_condition)(int*, int);

    //genera un nuevo individuo a partir de dos "padres"
    int* (*generate_child)(int*, int*, int);
    //numero maximo de iteraciones permitidas
    int max_iter;

    //numero de atributos que posee cada individuo
    int number_attr;

    //obtiene una lista de fitness para una poblacion
    int* (*get_fitness)(int**, int, int);
public:
    /*
     * constructor de Integer_GA
     */
    Integer_GA(int pop_size, double mutation_rate, int (*fitness)(int*,int),int* (*generate_child)(int*, int*, int) ,
            int* (*get_fitness)(int**, int, int) ,int** (*init_pop)(int, int), int*(*individual_generator)(int),
            int (*gen_generator)(), bool (*termination_condition)(int*, int), int* (*mutate)(int*, int), int** (*selection)(int**, int*, int), int max_iter, int number_attr);

    /*
     * metodo para correr el algoritmo genetico
     */
    void run();
};


#endif //T2_INTEGER_GA_H
