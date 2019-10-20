//
// Created by nikom on 18-10-2019.
//
#include "GA_T.h"
#include <ctime>
#include <cstdlib>
#include <random>
#include <fstream>


int numberOfChars = 77;
char wordToFind[78] = "hola como estas yo estoy bien haciendo la tarea de redes neuronales eso chaoo";
int population_size = 100;
double mutation_rate = 0.1;

std::random_device rd;
std::mt19937 gen(rd());

//funciones

/*
 * entrega el fitness de un individuo
 * @param resp lista de caracteristicas del individuo
 * @param number_char cantidad de caracteristicas (caracteres)
 * @return fitness
 * */
int fitness_word(char *resp, int number_char);

/*
 * genera un individuo (frase)
 * @param number_char cantidad de caracteristicas (caracteres)
 * @return array de caracteristicas del individuo generado
 */
char* word_factory(int number_char);

/*
 * genera el valor de un gen de un individuo (letras minusculas, mayusculas o espacio)
 * @return valor del gen
 */
char gen_generator();

/*
 * muta algun gen del individuo
 * @param res individuo a mutar
 * @param number_char cantidad de caracteristicas de un individuo (caracteres)
 * @return individuo mutado
 */
char* mutate(char* res, int number_char);

/*
 * crea una poblacion inicial aleatoria
 * @param population cantidad de individuos a crear
 * @param number_char cantidad de caracteristicas de un individuo (caracteres)
 * @return poblacion inicial
 */
char** init_pop(int population, int number_char);

/*
 * crea un nuevo individuo a partir de 2 padres
 * @param parent1 padre 1
 * @param parent2 padre 2
 * @param number_char cantidad de caracteristicas de un individuo (caracteres)
 *
 *@return individuo creado
 */
char* generate_child(char* parent1, char* parent2, int number_char);

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
char** seleccion(char** population_res, int* acc_fitness, int population);
int** shuffle(int** list, int n);
int* get_fitness(char** resp, int number_char, int population);
bool termination_word(char* res, int number_char);

/*
 * Obtiene el fitness acumulativo de una lista de fitnes ordenados
 * @param ordered_fitness lista de fitnes oredenada de menor a mayor
 * @param n tamaño de la lista de fitness
 * @return array de fitness acumulativo
 */
int* get_acc_fitness_word(int* ordered_fitness, int n);

int main() {

    srand(time(nullptr));
    auto *ga = new GA_T<char>(population_size, mutation_rate, fitness_word, generate_child, get_fitness, init_pop,
                             word_factory, gen_generator, termination_word,
                             mutate, seleccion,get_acc_fitness_word , 10000, numberOfChars);

//    for (int i = 0; i <50 ; ++i) {
//        std::cout << rand()%(-1000) << std::endl;
//    }
    ga->run();
    std::vector<int> forGraph = ga->getListBestFitness();
    int iters = ga->getIters();
    std::ofstream file("r1.txt");
    file << "Grafico para frase: '" << wordToFind << "'" << std::endl;
    file << numberOfChars << std::endl;
    file << population_size << std::endl;
    file << mutation_rate << std::endl;
    for(int i = 0; i < iters + 1; i++){
        file << forGraph[i] << "\n";
    }
    file.close();

}

int fitness_word(char *resp, int number_char){
    int result = 0;
    for(int i = 0; i < number_char; i++){
        if(resp[i] == wordToFind[i])
            result++;
    }
    return result;
}

char** init_pop(int population, int number_char){
    char** pop  = new char*[population];
    for(int i = 0; i < population; i++){
        pop[i] = word_factory(number_char);
    }
    return pop;
}

char gen_generator(){
    //caracteres codigo ascii [A-Z]= [65-90]   [a-z]=[97-122]  espacio=32
    int r = 65 + std::rand()%27;

    // espacio
    if(r == 91)
        return char(32);
    int r2 = std::rand()%2;

    //minusculas
    if(r2 == 1)
        r += 32;
    return char(r);


}
char* mutate(char* res, int number_char){
    int r = std::rand()%number_char;
    res[r] = gen_generator();
    return res;
}

char * generate_child(char* parent1, char* parent2, int number_char){
    int indice = std::rand()%number_char;
    char *child1 = new char[number_char];
    char *child2 = new char[number_char];
    //se crean dos hijos cada uno quedandose con una parte de cada padre
    for (int i = 0; i < number_char; ++i) {
        if(i < indice){
            child1[i] = parent1[i];
            child2[i] = parent2[i];
        }
        else{
            child1[i] = parent2[i];
            child2[i] = parent1[i];
        }
    }

    // se elige el hijo con mejor fitness
    if(fitness_word(child1, number_char) > fitness_word(child2, number_char)) {
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

char *word_factory(int number_char){
    char *res = new char[number_char + 1];
    for(int i = 0; i < number_char; i++)
        res[i] = gen_generator();
    res[number_char] = '\0';
    return res;
}

bool termination_word(char* res, int number_char){
    for(int i = 0; i < number_char; i++)
        if(res[i] != wordToFind[i])
            return false;
        return true;
}

int* get_fitness(char** resp, int number_char, int population){
    int* fitness = new int[population];
    for(int i = 0; i < population; i++)
        fitness[i] = fitness_word(resp[i], number_char);
//    quicksort(fitness, 0, population);
    return fitness;
}

char** seleccion(char** population_res, int* acc_fitness , int population){
    char ** selected = new char* [population];
    for(int i = 0; i < population; i++){
        int index = getRandomIndex(acc_fitness, population);
        selected[i] = population_res[index];
    }

    return selected;

}

int* get_acc_fitness_word(int* ordered_fitness, int n){
    int acc = 0;
    int* acc_fitness = new int[n];
    for(int i = 0; i < n; i++){
        acc += ordered_fitness[i];
        acc_fitness[i] = acc;
    }
    return acc_fitness;
}