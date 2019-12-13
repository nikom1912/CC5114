//
// Created by nikom on 11-12-2019.
//

#include <vector>

//int get_index_max(int* list, int n);
//
//int convert_bits_int(int* bits, int n);

template <typename T>
void my_extend(std::vector<T>* a, std::vector<T>* b){
    T* sds= b->data();
//    for(auto el = b->begin(); el != b->end(); b++){
//        a->push_back(*el);
//    }
for(int i = 0; i < b->size(); i++)
    a->push_back(sds[i]);
}

//template <typename T> void quicksort_2(int *array, T** pop, int start, int end);
//
//template <typename T> int divide_2(int *array, T** pop, int start, int end);

template<typename T> void ordenarArray(int* miArray, T* pop, int n);
//void quicksort(int *array, int start, int end);
//int divide(int *array, int start, int end);






//int convert_bits_int(int* bits, int n){
//    int result = 0;
//    int exp = 1;
//    for(int i = 0; i < n; i++){
//        result += bits[i] *exp;
//        exp *=2;
//    }
//    return result;
//}
//
//// Función recursiva para hacer el ordenamiento
//void quicksort(int *array, int start, int end)
//{
//    int pivot;
//
//    if (start < end) {
//        pivot = divide(array, start, end);
//
//        // Ordeno la lista de los menores
//        quicksort(array, start, pivot - 1);
//
//        // Ordeno la lista de los mayores
//        quicksort(array, pivot + 1, end);
//    }
//}
//// Función para dividir el array y hacer los intercambios
//
//int divide(int *array, int start, int end) {
//    int left;
//    int right;
//    int pivot;
//    int temp;
//
//    pivot = array[start];
//    left = start;
//    right = end;
//
//    // Mientras no se cruzen los índices
//    while (left < right) {
//        while (array[right] > pivot) {
//            right--;
//        }
//
//        while ((left < right) && (array[left] <= pivot)) {
//            left++;
//        }
//
//        // Si todavía no se cruzan los indices seguimos intercambiando
//        if (left < right) {
//            temp = array[left];
//            array[left] = array[right];
//            array[right] = temp;
//        }
//    }
//
//    // Los índices ya se han cruzado, ponemos el pivot en el lugar que le corresponde
//    temp = array[right];
//    array[right] = array[start];
//    array[start] = temp;
//
//    // La nueva posición del pivot
//    return right;
//}
//
template <typename T>
void ordenarArray(int* miArray, T* pop, int n){
    int temporal;
    T temp2;
    for (int i = 0;i < n; i++){
        for (int j = 0; j< n-1; j++){
            if (miArray[j] > miArray[j+1]){ // Ordena el array de mayor a menor, cambiar el "<" a ">" para ordenar de menor a mayor
                temporal = miArray[j];
                temp2 = pop[j];
                miArray[j] = miArray[j+1];
                pop[j] = pop[j + 1];
                miArray[j+1] = temporal;
                pop[j + 1] = temp2;
            }
        }
    }
}
//template <typename T>
//void quicksort_2(int *array, T** pop, int start, int end)
//{
//    int pivot;
//
//    if (start < end) {
//        pivot = divide_2(array,pop, start, end);
//
//        // Ordeno la lista de los menores
//        quicksort_2(array, pop ,start, pivot - 1);
//
//        // Ordeno la lista de los mayores
//        quicksort_2(array, pop, pivot + 1, end);
//    }
//}
//// Función para dividir el array y hacer los intercambios
//
//template <typename T>
//int divide_2(int *array, T** pop, int start, int end) {
//    int left;
//    int right;
//    int pivot;
//    int temp;
//    T *temp2;
//
//    pivot = array[start];
//    left = start;
//    right = end;
//
//    // Mientras no se cruzen los índices
//    while (left < right) {
//        while (array[right] > pivot) {
//            right--;
//        }
//
//        while ((left < right) && (array[left] <= pivot)) {
//            left++;
//        }
//
//        // Si todavía no se cruzan los indices seguimos intercambiando
//        if (left < right) {
//            temp = array[left];
//            temp2 = pop[left];
//            array[left] = array[right];
//            pop[left] = pop[right];
//            array[right] = temp;
//            pop[right] = temp2;
//        }
//    }
//
//    // Los índices ya se han cruzado, ponemos el pivot en el lugar que le corresponde
//    temp = array[right];
//    temp2 = pop[right];
//    array[right] = array[start];
//    pop[right] = pop[start];
//    pop[start] = temp2;
//    array[start] = temp;
//
//    // La nueva posición del pivot
//    return right;
//}
//
//
