## Instrucciones de uso
Este codigo fue hecho en clion windows usando Mingw como compilador, por ende, se recomienda uso de estos software para el correcto funcionamiento,
la tarea no se ha probado en Linux, pero se incluye un makefile para compilar con g++ el cual fue probado con exito en WSL.

## Funcionamiento

Para realizar la tarea se hace uso de la clase GA_T<T>  la cual permite correr algoritmos geneticos para poblaciones cuyos individuos tienen un tamaño
fijo de caracteristicas y todas son de tipo T.
La clase recibe todo lo necesario para correr el GA, tamaño de la poblacion, numero de genes por individuo, mutation rate,
maximo de iteraciones antes de terminar y las distintas funciones que se requieren , como un inicializador de la poblacion, una funcion de seleccion, de mutacion, de generacion de un individuo, etc.

## Analisis

#### Bits
Para el caso de los bits se realizo un acercamiento similar al visto en clases, pero se cambio la funcion fitness
para que los valores entregados fueran positivos, para ello se obtuvo un fitness maximo igual a la maxima distancia posible que se podia estar del numero a convertir (dsitancia = abs(valor - numero a convertir))
este fitness maximo es igual a max(abs(pow(2, number of bits) - numero a encontrar), numero a encontrar) y el fitness de cada valor es igual
a maximoFitness - abs(obtenido - real)
Usando esto el algoritmo funciona casi a la perfeccion, generalmente encontrando la respuesta antes de la decima iteracion
con un tamaño de poblacion de 100 y numero de bits igual a 16.
Se nota la aparicion de ciertos problemas, a veces el algoritmo se queda pegado en un valor, usualmente muy cercano al valor buscado,
esto puede deberse a la convergencia de la poblacion a este resultado o a un problema de implementacion, el cual no he notado, o tambien puede deberse a lo irregular que puede resultar el uso de random, lo que tambien puede
relacionarse con el primer caso.

#### Word
Se uso una implementacion similar a Bits, con la diferencia de que ahora un gen no es solo 0 o 1, si no que ahora tiene 53 valores (26 minusculas, 26 mayusculas y espacio).
El fitness se calcula viendo en cada caracter del arreglo de caracteres dado y el arreglo generado si los valores coinciden, en cuyo caso se suma 1 al fitness, o si no, en cuyo caso no se suma nada,
con esto el maximo fitness es igual al largo de la frase a buscar.
La implementacion dada funciona perfectamente, logrando encontrar la respuesta para una secuencia de caracteres de largo 76, una poblacion inicial de 100 y mutation rate igual 0.1, en unos 2500 iteraciones.
Este problema se puede graficar, para ello se corre el archivo compilado de main_word.cpp, lo que generara un archivo de texto "r1.txt" con los fitness de cada generacion, en la carpeta 'cmake-build-debug', luego se corre el archivo graficar.py para ver el resultado.

#### 0-1-knapsack
Para este problema el resultado se muestra como una secuencia de 0s y 1s de largo igual a la cantidad de cajas, dado que solo se puede usar una caja una vez
lo unico que nos importa es si uso o no la caja, lo que se marca con 1 o 0 respectivamente, para el fitness se tomo en cuenta tanto la diferencia con el peso maximo
de la mochila como el valor total de las cajas, dado que las cajas deben caer en la mochila, cualquier combinacion que se pasa del peso maximo recibe 0 de fitness.
Dada lo irregular que puede ser el resultado del problema al cambiar el peso maximo de la mochila o
la cantidad y tipos de cajas, no se tiene otra condicion de termino mas que el maximo de iteraciones.
En general, la respuesta mas acertada con peso maximo igual a 15, mutation rate de 0.1 , 5 cajas y tamaño de la poblacion de 5, es encontrada antes de las 100 iteraciones.