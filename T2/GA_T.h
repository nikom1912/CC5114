//
// Created by nikom on 18-10-2019.
//

#ifndef T2_GA_T_H
#define T2_GA_T_H

#include <string>
#include <iostream>
#include "utils.h"
#include <vector>
template <typename T>
class GA_T {
private:
    int pop_size;
    double mutation_rate;
    T** (*init_pop)(int, int);
    int (*fitness)(T*, int);
    T * (*individual_generator)(int);
    T (*gen_generator)();
    T ** (* selection)(T**, int*, int);
    T* (*mutate)(T*, int);
    bool (*termination_condition)(T*, int);
    T* (*generate_child)(T*, T*, int);
    int max_iter;
    int number_attr;
    int* (*get_fitness)(T**, int, int);
    int* (*get_acc_fitness)(int*, int);
    std::vector<int> best_fitness;
    std::vector<T*> best_list;
    int total_iters;

public:
    GA_T(int pop_size, double mutation_rate, int (*fitness)(T*,int),T* (*generate_child)(T*, T*, int) ,
               int* (*get_fitness)(T**, int, int) ,T** (*init_pop)(int, int), T*(*individual_generator)(int),
               T (*gen_generator)(), bool (*termination_condition)(T*, int), T* (*mutate)(T*, int), T** (*selection)(T**, int*, int)
             ,int* (*get_acc_fitness)(int*, int), int max_iter, int number_attr);

    void run();
    std::vector<int> getListBestFitness();
    int getIters();
    std::vector<T*> getBestList();
};

template<typename T>
GA_T<T>::GA_T(int pop_size, double mutation_rate, int (*fitness)(T *, int), T *(*generate_child)(T *, T *, int),
              int *(*get_fitness)(T**, int, int), T **(*init_pop)(int, int), T *(*individual_generator)(int),
              T (*gen_generator)(), bool (*termination_condition)(T *, int), T *(*mutate)(T *, int),
              T **(*selection)(T **, int *, int), int* (*get_acc_fitness)(int*, int), int max_iter, int number_attr) {
    this->pop_size = pop_size;
    this->number_attr = number_attr;
    this->mutation_rate = mutation_rate;
    this->fitness = fitness;
    this->individual_generator = individual_generator;
    this->gen_generator = gen_generator;
    this->termination_condition = termination_condition;
    this->mutate = mutate;
    this->selection = selection;
    this->init_pop = init_pop;
    this->max_iter = max_iter;
    this->generate_child = generate_child;
    this->get_fitness = get_fitness;
    this->get_acc_fitness = get_acc_fitness;
    this->best_fitness = std::vector<int>();
}

template <typename T>
void GA_T<T>::run(){
    T** pop= this->init_pop(pop_size, number_attr);
    int iter = 0;
    int* fitness_list = get_fitness(pop, number_attr, pop_size);
    ordenarArray(fitness_list, pop, pop_size);
    T ** selected;
    int * acc_fitness = get_acc_fitness(fitness_list, pop_size);
    T *child;
    T* best = pop[pop_size - 1];
//    int res_ant = convert_bits_int(best, number_attr);
    best_fitness.push_back(fitness(best, number_attr));
    while(not termination_condition(best, number_attr) && iter < max_iter){
        selected = selection(pop, acc_fitness, pop_size);
//        free(pop);
        for(int i = 0; i < pop_size; i++) {
            if(i == pop_size - 1 )
                child = generate_child(selected[i], selected[0], number_attr);
            else
                child = generate_child(selected[i], selected[i + 1], number_attr);
            double r = (std::rand() % 1000) / 1000.0;
            if (r < mutation_rate)
                mutate(child, number_attr);
            pop[i] = child;
        }
        fitness_list = get_fitness(pop, number_attr, pop_size);

        ordenarArray(fitness_list, pop, pop_size);
        best = pop[pop_size -1];
        best_list.push_back(best);
        best_fitness.push_back(fitness_list[pop_size - 1]);
        acc_fitness = get_acc_fitness(fitness_list, pop_size);
        iter++;
        std::cout << "Best response GEN " << iter
                  << " : ";
        for(int i = 0; i < number_attr; i++)
            std::cout << best[i];
        std::cout << std::endl;

    }
    total_iters = iter;
}

template<typename T>
std::vector<int> GA_T<T>::getListBestFitness() {
    return best_fitness;
}

template<typename T>
int GA_T<T>::getIters() {
    return total_iters;
}

template<typename T>
std::vector<T *> GA_T<T>::getBestList() {
    return best_list;
}


#endif //T2_GA_T_H
