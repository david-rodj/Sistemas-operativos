/*****************************************************
Pontificia Universidad Javeriana
Autor: David rodriguez
Fecha: 29/10/2024
Materia: Sistemas operativos
Tema: MaquinaVirtual hilos
*****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/**
 * @brief Función que será ejecutada por cada hilo.
 * 
 * Esta función recibe un puntero a un argumento, que se espera que sea un puntero a un
 * tamaño (size_t) que representa el trabajo asignado a ese hilo. La función imprime el
 * número del trabajo que está ejecutando.
 * 
 * @param argumentos Puntero a los argumentos que se pasan a la función. Se espera que
 *                   sea un puntero a un tamaño (size_t).
 * @return NULL Siempre retorna NULL al finalizar.
 */
static void *funcion(void *argumentos) {
    size_t job = *(size_t *)argumentos; // Desreferencia el puntero para obtener el trabajo
    printf("\n\t Job %zu \n", job);      // Imprime el número del trabajo
    return NULL;                         // Retorna NULL al finalizar
}

int main(int argc, char *argv[]) {
    // Verifica que se haya pasado un argumento al programa
    if (argc < 2) {
        fprintf(stderr, "Uso: %s <número de hilos>\n", argv[0]);
        return 1; // Retorna 1 si no se pasa el argumento
    }

    int N = (int)atoi(argv[1]); // Convierte el argumento a un entero
    size_t jobs[N];             // Vector para almacenar los trabajos (números de trabajo)
    pthread_t hilos[N];         // Vector para almacenar los identificadores de los hilos

    // Bucle para crear N hilos
    for (int i = 0; i < N; i++) {
        jobs[i] = i; // Asigna el número de trabajo al vector jobs
        // Creación de hilos y envío de la función 'funcion' con el trabajo correspondiente
        pthread_create(&hilos[i], NULL, funcion, jobs + i);
    }

    // Bucle para esperar a que todos los hilos terminen su ejecución
    for (int i = 0; i < N; i++)
        pthread_join(hilos[i], NULL); // Espera a que el hilo i termine

    return 0; // Retorna 0 al finalizar el programa correctamente
}
