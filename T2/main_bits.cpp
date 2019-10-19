//#include "utils.cpp"
#include "GA_T.h"
#include <ctime>
#include <cstdlib>
#include <random>


//caracteristicas de la poblacion
int numberOfBits = 16;
int numberToConvert = 22598;
int population_size = 100;
double mutation_rate = 0.1;


//setea el random_device
std::random_device rd;
std::mt19937 gen(rd());

//funciones

/*
 * entrega el fitness de un individuo
 * @param resp lista de caracteristicas del individuo
 * @param number_bits cantidad de caracteristicas
 * @return fitness
 * */
int fitness_bits(int *resp, int number_bits);

/*
 * genera un individuo
 * @param number_bits cantidad de caracteristicas
 * @return array de caracteristicas del individuo generado
 */
int *sequence_bit_factory(int number_bits);

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
 * @param number_bits cantidad de caracteristicas de un individuo
 * @return individuo mutado
 */
int* mutate(int* res, int number_bits);

/*
 * crea una poblacion inicial aleatoria
 * @param population cantidad de individuos a crear
 * @param number_bits cantidad de caracteristicas de un individuo
 * @return poblacion inicial
 */
int** init_pop(int population, int number_bits);

/*
 * crea un nuevo individuo a partir de 2 padres
 * @param parent1 padre 1
 * @param parent2 padre 2
 * @param number_bits cantidad de caracteristicas de un individuo
 *
 *@return individuo creado
 */
int * generate_child(int* parent1, int* parent2, int number_bits);

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
 * @param number_bits cantidad de caracteristicas de un individuo
 * @param population cantidad de individuos en la poblacion
 * @return lista de fitness
 */
int* get_fitness(int** resp, int number_bits, int population);

/*
 * Entrega true si se consigue la condicion de termino para el GA
 * @param resp mejor individuo de la generacion
 * @param number_bits cantidad de caracteristicas de un individuo
 * @return true o false
 */
bool termination_bits(int* res, int number_bits);

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::srand(time(nullptr));
    std::cout << pow(2, numberOfBits) << std::endl;
    auto ga = new GA_T<int>(population_size, mutation_rate, fitness_bits, generate_child, get_fitness, init_pop,
                     sequence_bit_factory, gen_generator, termination_bits,
                     mutate, seleccion, get_acc_fitness ,100000, numberOfBits);

//    for (int i = 0; i <50 ; ++i) {
//        std::cout << rand()%(-1000) << std::endl;
//    }
    ga->run();
    std::cout << "number to convert: " << numberToConvert << std::endl;

}

int fitness_bits(int *resp, int number_bits){
    int result = 0;
    int exp = 1;
    int max_valor = pow(2, number_bits);
    int max_fitness = std::max(abs(max_valor - numberToConvert), numberToConvert);
    for(int i = 0; i < number_bits; i++){
        result += resp[i] *exp;
        exp *=2;
    }
//    std::cout << "result      " << result << " ------fitness  "<< max_fitness - abs(numberToConvert - result)<<std::endl;
    return max_fitness - abs(numberToConvert - result);
}

int** init_pop(int population, int number_bits){
    int** pop  = new int*[population];
    for(int i = 0; i < population; i++)
        pop[i] = new int[number_bits];
    for(int i = 0; i < population; i++){
        pop[i] = sequence_bit_factory(number_bits);
    }
    return pop;
}

int gen_generator(){
    int r = rand()%1000;
    if(r < 500)
        return 1;
    else
        return 0;
}
int* mutate(int* res, int number_bits){

    int r = std::rand()%number_bits;
    res[r] = gen_generator();
    return res;
}

int * generate_child(int* parent1, int* parent2, int number_bits){
    int indice = std::rand()%number_bits;;
    int *child1 = new int[number_bits];
    int *child2 = new int[number_bits];
    for (int i = 0; i < number_bits; ++i) {
        if(i < indice){
            child1[i] = parent1[i];
            child2[i] = parent2[i];
        }
        else{
            child1[i] = parent2[i];
            child2[i] = parent1[i];
        }
    }
    if(fitness_bits(child1, number_bits) > fitness_bits(child2, number_bits)) {
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
int *sequence_bit_factory(int number_bits){
    int *res = new int[number_bits];
    for(int i = 0; i < number_bits; i++)
        res[i] = gen_generator();
    return res;
}

bool termination_bits(int* res, int number_bits){
    int max_valor = pow(2, number_bits);
    int max_fitness = std::max(abs(max_valor - numberToConvert), numberToConvert);
    return fitness_bits(res, number_bits) == max_fitness;

}

int* get_fitness(int** resp, int number_bits, int population){
    int* fitness = new int[population];
    for(int i = 0; i < population; i++)
        fitness[i] = fitness_bits(resp[i], number_bits);
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


/*
 * Obtiene el accumualte fitness a partir de una lista de fitnes ordenadas de menor a mayor
 */
int* get_acc_fitness(int* ordered_fitness, int n){
    int acc = 0;
    int* acc_fitness = new int[n];
    for(int i = 0; i < n; i++){
        acc += ordered_fitness[i];
        acc_fitness[i] = acc;
    }
    return acc_fitness;
}
