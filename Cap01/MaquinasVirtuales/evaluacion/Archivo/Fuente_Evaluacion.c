/**************************************************************
Pontificia Universidad Javeriana
Autor: David Rodriguez
Fecha: Octubre 2024
Materia: Sistemas Operativos
Tema: Taller de Evaluación de Rendimiento
Fichero: fuente de multiplicación de matrices NxN por hilos.
Objetivo: Evaluar el tiempo de ejecución del 
	  algoritmo clásico de multiplicación de matrices.
	  Se implementa con la Biblioteca POSIX Pthreads
****************************************************************/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#define DATA_SIZE (1024*1024*64*3) // Definición del tamaño de los datos en memoria

pthread_mutex_t MM_mutex; // Mutex para sincronización
static double MEM_CHUNK[DATA_SIZE]; // Chunk de memoria para las matrices
double *mA, *mB, *mC; // Punteros para las matrices A, B y C

struct parametros {
	int nH; // Número de hilos
	int idH; // ID del hilo
	int N; // Tamaño de la matriz
};

struct timeval start, stop; // Estructuras para medir el tiempo

/**
 * @brief Llena las matrices A y B con valores predefinidos.
 *
 * Esta función inicializa las matrices A y B con valores 
 * secuenciales y establece la matriz C en cero.
 *
 * @param SZ Tamaño de la matriz (número de filas/columnas).
 */
void llenar_matriz(int SZ) { 
	srand48(time(NULL)); // Inicializa la semilla para la generación aleatoria
	for(int i = 0; i < SZ * SZ; i++) {
		mA[i] = 1.1 * i; // Asigna valores a la matriz A
		mB[i] = 2.2 * i; // Asigna valores a la matriz B
		mC[i] = 0; // Inicializa la matriz C en cero
	}	
}

/**
 * @brief Imprime una matriz en la consola.
 *
 * Esta función imprime la matriz en un formato legible si su 
 * tamaño es menor a 12. De lo contrario, solo imprime un separador.
 *
 * @param sz Tamaño de la matriz (número de filas/columnas).
 * @param matriz Puntero a la matriz que se desea imprimir.
 */
void print_matrix(int sz, double *matriz) {
	if(sz < 12) {
		for(int i = 0; i < sz * sz; i++) {
			if(i % sz == 0) printf("\n");
			printf(" %.3f ", matriz[i]);
		}	
	}
    printf("\n>-------------------->\n");
}

/**
 * @brief Inicia el conteo del tiempo.
 *
 * Esta función captura el tiempo actual y lo almacena en la variable 
 * 'start' para su posterior uso en la medición del tiempo de ejecución.
 */
void inicial_tiempo() {
	gettimeofday(&start, NULL); // Captura el tiempo actual
}

/**
 * @brief Finaliza el conteo del tiempo y muestra el resultado.
 *
 * Esta función captura el tiempo final y calcula la diferencia con 
 * respecto al tiempo inicial, mostrando el tiempo de ejecución en 
 * microsegundos.
 */
void final_tiempo() {
	gettimeofday(&stop, NULL); // Captura el tiempo final
	stop.tv_sec -= start.tv_sec; // Calcula la diferencia de segundos
	printf("\n:-> %9.0f µs\n", (double) (stop.tv_sec * 1000000 + stop.tv_usec)); // Muestra el tiempo en microsegundos
}

/**
 * @brief Función que ejecuta la multiplicación de matrices en hilos.
 *
 * Esta función es ejecutada por cada hilo y realiza la multiplicación 
 * de matrices dividiendo el trabajo entre los hilos.
 *
 * @param variables Puntero a una estructura de parámetros que contiene 
 *                  información sobre el hilo y el tamaño de la matriz.
 * @return NULL
 */
void *mult_thread(void *variables) {
	struct parametros *data = (struct parametros *)variables; // Cast a la estructura de parámetros
	
	int idH = data->idH; // ID del hilo
	int nH  = data->nH; // Número total de hilos
	int N   = data->N; // Tamaño de la matriz
	int ini = (N / nH) * idH; // Índice inicial para el hilo
	int fin = (N / nH) * (idH + 1); // Índice final para el hilo

    // Realiza la multiplicación de matrices para la parte asignada al hilo
