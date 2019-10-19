//
// Created by nikom on 08-10-2019.
//

//#ifndef  T2_UTILS_CPP
//#include "utils.cpp"
//#endif
#include "Integer_GA.h"

Integer_GA::Integer_GA(const int pop_size, double mutation_rate, int (*fitness)(int*,int), int* (*generate_child)(int*, int*, int),int* (*get_fitness)(int**, int, int) , int** (*init_pop)(int, int), int*(*individual_generator)(int), int (*gen_generator)(),
        bool (*termination_condition)(int*, int), int* (*mutate)(int*, int), int** (*selection)(int**, int*, int), int max_iter,const int number_attr){
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

}

void Integer_GA::run() {
//    const int pop_size_const = pop_size;
//    const int number_attr_const = number_attr;
    int** pop= this->init_pop(pop_size, number_attr);
//    for(int i = 0; i < pop_size ; i++) {
//        std::cout << "iter " << i << " " ;
//        for (int j = 0; j < number_attr; j++) {
//            std::cout << pop[i][j];
//        }
//        std::cout << std::endl;
//    }
//    std::cout << "holia" << std::endl;

    int iter = 0;
    int* fitness_list = get_fitness(pop, number_attr, pop_size);
    quicksort_bits(fitness_list, pop, 0, pop_size - 1);
    int ** selected;
    int * acc_fitness = get_acc_fitness(fitness_list, pop_size);
    int *child;
    int* best = pop[pop_size - 1];
    int res_ant = convert_bits_int(best, number_attr);
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
        quicksort_bits(fitness_list, pop, 0 , pop_size - 1);
        best = pop[pop_size - 1];
        acc_fitness = get_acc_fitness(fitness_list, pop_size);
        iter++;
        int res = convert_bits_int(best, number_attr);

//        std::cout << "AANTTTTTTTTTTTTTTTTTTT "<< convert_bits_int(pop[0], number_attr) << std::endl;
        std::cout << "Best response GEN " << iter
            << " : " << res << std::endl;
        int res_ant = res;
    }
}
