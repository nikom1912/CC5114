//
// Created by nikom on 18-10-2019.
//
#include "GA_T.h"
#include <ctime>
#include <cstdlib>
#include <random>


/*
 * estructura que guarda las caracteristicas de una caja (peso y valor)
 */
typedef struct{
    int peso;
    int valor;
} knapbox;

// boxes que se pueden usar (solo 1)
knapbox boxes[5] = {{12,4}, {2,2},{1,2}, {1, 1}, {4, 10}};

//caracteristicas de la poblacion
int numberOfBoxes = 5;
int peso_mochila = 15;
int population_size = 5;
double mutation_rate = 0.1;


//setea el random_device
std::random_device rd;
std::mt19937 gen(rd());

//funciones

/*
 * entrega el fitness de un individuo
 * @param resp lista de caracteristicas del individuo
 * @param number_boxes cantidad de caracteristicas
 * @return fitness
 * */
int fitness_knap(int *resp, int number_boxes);

/*
 * genera un individuo
 * @param number_boxes cantidad de caracteristicas
 * @return array de caracteristicas del individuo generado
 */
int *sequence_knap_factory(int number_boxes);

/*
 * Obtiene el fitness acumulativo de una lista de fitnes ordenados
 * @param ordered_fitness lista de fitnes oredenada de menor a mayor
 * @param n tamaño de la lista de fitness
 * @return array de fitness acumulativo
 */
int* get_acc_fitness(int* ordered_fitness, int n);

/*
 * genera el valor de un gen de un individuo (0 o 1)
 * @return valor del gen
 */
int gen_generator();

/*
 * muta algun gen del individuo
 * @param res individuo a mutar
 * @param number_boxes cantidad de caracteristicas de un individuo
 * @return individuo mutado
 */
int* mutate(int* res, int number_boxes);

/*
 * crea una poblacion inicial aleatoria
 * @param population cantidad de individuos a crear
 * @param number_boxes cantidad de caracteristicas de un individuo
 * @return poblacion inicial
 */
int** init_pop(int population, int number_boxes);

/*
 * crea un nuevo individuo a partir de 2 padres
 * @param parent1 padre 1
 * @param parent2 padre 2
 * @param number_boxes cantidad de caracteristicas de un individuo
 *
 *@return individuo creado
 */
int * generate_child(int* parent1, int* parent2, int number_boxes);

/*
 * obtiene un indice random a partir de un fitness acumulado (ruleta)
 * @param acc_fitness lista de fitness acumulado
 * @param n largo de la lista de fitness
 * @return indice
 */
int getRandomIndex(int *acc_fitness, int n);

/*
 * Realiza la seleccion de los individuos que participaran en el crossover
 * @param population_res poblacion de la cual se seleccionara
 * @param acc_fitness lista de fitness acumulado
 * @param population cantidad de individuos en la poblacion
 * @return array de individuos seleccionados
 */
int** seleccion(int** population_res, int* acc_fitness, int population);

/*
 * obtiene una lista de fitness para la poblacion
 * @param resp poblacion
 * @param number_boxes cantidad de caracteristicas de un individuo
 * @param population cantidad de individuos en la poblacion
 * @return lista de fitness
 */
int* get_fitness(int** resp, int number_boxes, int population);

/*
 * Entrega true si se consigue la condicion de termino para el GA
 * @param resp mejor individuo de la generacion
 * @param number_bits cantidad de caracteristicas de un individuo
 * @return true o false
 */
bool termination_knap(int* res, int number_boxes);

int main() {

    srand(time(nullptr));


    auto *ga = new GA_T<int>(population_size, mutation_rate, fitness_knap, generate_child, get_fitness, init_pop,
                              sequence_knap_factory, gen_generator, termination_knap,
                              mutate, seleccion, get_acc_fitness, 100, numberOfBoxes);

//    for (int i = 0; i <50 ; ++i) {
//        std::cout << rand()%(-1000) << std::endl;
//    }
    ga->run();

}

int fitness_knap(int *resp, int number_boxes){
    int valor_total = 0;
    int peso_total = 0;
    int result;
    for(int i = 0; i < number_boxes; i++ ){
        if(resp[i] == 1){
            peso_total += boxes[i].peso;
            valor_total += boxes[i].valor;
        }
    }
    int dif_pesos = peso_mochila - peso_total;
    if( dif_pesos < 0){
        result = dif_pesos;
        return 0;
    }
    else
        result = - dif_pesos;
    result += valor_total;
    return std::max(0, result);
}

int** init_pop(int population, int number_boxes){
    int** pop  = new int*[population];
    for(int i = 0; i < population; i++)
        pop[i] = new int[number_boxes];
    for(int i = 0; i < population; i++){
        pop[i] = sequence_knap_factory(number_boxes);
    }
    return pop;
}

int gen_generator(){
    int r = std::rand()%100;
    if(r < 50)
        return 1;
    else
        return 0;
}
int* mutate(int* res, int number_boxes){
    int r = std::rand()%number_boxes;
    res[r] = gen_generator();
    return res;
}

int * generate_child(int* parent1, int* parent2, int number_boxes){
    int indice = std::rand()%number_boxes;
    int *child1 = new int[number_boxes];
    int *child2 = new int[number_boxes];
    for (int i = 0; i < number_boxes; ++i) {
        if(i < indice){
            child1[i] = parent1[i];
            child2[i] = parent2[i];
        }
        else{
            child1[i] = parent2[i];
            child2[i] = parent1[i];
        }
    }
    if(fitness_knap(child1, number_boxes) > fitness_knap(child2, number_boxes)) {
        free(child2);
        return child1;
    }
    free(child1);
    return child2;
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
int *sequence_knap_factory(int number_boxes){
    int *res = new int[number_boxes];
    for(int i = 0; i < number_boxes; i++)
        res[i] = gen_generator();
    return res;
}

bool termination_knap(int* res, int number_boxes){
    return fitness_knap(res, number_boxes) == -2;

}

int* get_fitness(int** resp, int number_boxes, int population){
    int* fitness = new int[population];
    for(int i = 0; i < population; i++)
        fitness[i] = fitness_knap(resp[i], number_boxes);
//    quicksort(fitness, 0, population);
    return fitness;
}

int** seleccion(int** population_res, int* acc_fitness , int population){
    int ** selected = new int* [population];
    for(int i = 0; i < population; i++){
        int index = getRandomIndex(acc_fitness, population);
//        std::cout << "index  " << index << std::endl;
        selected[i] = population_res[index];
    }
    return selected;

}

int* get_acc_fitness(int* ordered_fitness, int n){
    int acc = 0;
    int min = ordered_fitness[0];
    int* acc_fitness = new int[n];
//    for(int i = 0; i < n ; i++)
//        aux_fitness[i] -= min;
    for(int i = 0; i < n; i++){
        acc += ordered_fitness[i];
        acc_fitness[i] = acc;
    }
    return acc_fitness;
}
