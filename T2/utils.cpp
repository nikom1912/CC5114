//
// Created by nikom on 16-10-2019.
//




//void quicksort(int *array, char** pop, int start, int end)
//{
//    int pivot;
//
//    if (start < end) {
//        pivot = divide(array,pop, start, end);
//
//        // Ordeno la lista de los menores
//        quicksort(array, pop ,start, pivot - 1);
//
//        // Ordeno la lista de los mayores
//        quicksort(array, pop, pivot + 1, end);
//    }
//}
//
//// Función para dividir el array y hacer los intercambios
//int divide(int *array, char** pop, int start, int end) {
//    int left;
//    int right;
//    int pivot;
//    int temp;
//    char *temp2;
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
//int get_index_max(int* list, int n){
//    int index = 0;
//    int max = list[0];
//    for(int i = 1; i < n; i++)
//        if(list[i] > max) {
//            index = i;
//            max = list[i];
//        }
//    return max;
//}