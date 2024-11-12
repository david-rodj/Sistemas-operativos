/******************************************************************
Pontificia Universidad Javeriana
Autor: David Rodríguez
Fecha: 27/08/2024
Materia: Sistemas operativos
Tema: Posix y Mutex - productor y consumidor
******************************************************************/

/**
 * @brief Implementación de un modelo productor-consumidor utilizando hilos en C.
 * 
 * Este programa utiliza la biblioteca pthread para crear múltiples hilos que actúan como 
 * productores y consumidores. Los productores incrementan un contador compartido, mientras 
 * que los consumidores lo decrementan. Se utilizan mutexes y variables de condición para 
 * sincronizar el acceso al contador y evitar condiciones de carrera.
 */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

int counter = 0;  // Contador compartido entre productores y consumidores
int max = 4;      // Número máximo de hilos productores y consumidores

// Inicialización de mutexes para la sincronización
pthread_mutex_t counter_mutex = PTHREAD_MUTEX_INITIALIZER; // Mutex para proteger el acceso al contador
pthread_mutex_t condp_mutex = PTHREAD_MUTEX_INITIALIZER;   // Mutex para la condición del productor
pthread_mutex_t condc_mutex = PTHREAD_MUTEX_INITIALIZER;   // Mutex para la condición del consumidor
pthread_mutex_t condVarProd = PTHREAD_MUTEX_INITIALIZER;    // Variable de condición para el productor
pthread_mutex_t condVarCons = PTHREAD_MUTEX_INITIALIZER;    // Variable de condición para el consumidor

/**
 * @brief Función que representa el comportamiento del hilo consumidor.
 * 
 * Esta función se ejecuta en un bucle infinito, donde el consumidor espera a que haya 
 * elementos disponibles en el contador para consumir. Utiliza mutexes y variables de 
 * condición para sincronizar el acceso al contador.
 * 
 * @return NULL
 */
void *consumidor();

/**
 * @brief Función que representa el comportamiento del hilo productor.
 * 
 * Esta función se ejecuta en un bucle infinito, donde el productor incrementa el contador 
 * hasta un máximo de 10. Utiliza mutexes y variables de condición para sincronizar el 
 * acceso al contador.
 * 
 * @return NULL
 */
void *productor();

/**
 * @brief Función principal del programa.
 * 
 * Crea hilos para los productores y consumidores, y espera a que todos los hilos terminen 
 * su ejecución. Se utiliza un bucle para crear un número máximo de hilos definidos por la 
 * variable `max`.
 * 
 * @param argc Número de argumentos de línea de comandos.
 * @param argv Arreglo de argumentos de línea de comandos.
 * @return 0 si se ejecuta correctamente.
 */
int main(int argc, char *argv[]){
    pthread_t prodHilo[max]; // Vector de hilos productor
    pthread_t consHilo[max]; // Vector de hilos consumidor

    // Creación de hilos y envío de función Productor o Consumidor
    for(int i=0; i<max; i++){
        pthread_create(&prodHilo[i], NULL, &productor, NULL);
        pthread_create(&consHilo[i], NULL, &consumidor, NULL);
    }

    // Espera a que todos los hilos terminen su ejecución
    for(int i=0; i<max; i++){
        pthread_join(prodHilo[i], NULL);
        pthread_join(consHilo[i], NULL);
    }
    return 0;
}

/**
 * @brief Implementación de la función productor.
 * 
 * El productor incrementa el contador compartido. Si el contador alcanza 10, el productor 
 * espera hasta que haya espacio disponible. Cuando produce un elemento, notifica al 
 * consumidor. Si el contador supera 7, el productor duerme durante 4 segundos.
 * 
 * @return NULL
 */
void *productor(){
    while(1){
        pthread_mutex_lock(&condp_mutex); // Bloquea el mutex para la condición del productor
        while(counter >= 10) // Si el contador está lleno, espera
            pthread_cond_wait(&condVarProd, &condp_mutex);
        pthread_mutex_unlock(&condp_mutex); // Desbloquea el mutex de condición del productor

        pthread_mutex_lock(&counter_mutex); // Bloquea el mutex para el contador
        counter++; // Incrementa el contador
        pthread_cond_signal(&condVarCons); // Notifica al consumidor que hay un nuevo elemento
        printf("Soy el PRODUCTOR %d || Contador = %d\n", pthread_self(), counter);
        pthread_mutex_unlock(&counter_mutex); // Desbloquea el mutex del contador

        // Si el contador es mayor que 7, duerme durante 4 segundos
        if(counter > 7)
            sleep(4);
    }
}

/**
 * @brief Implementación de la función consumidor.
 * 
 * El consumidor decrementa el contador compartido. Si el contador está vacío, el consumidor 
 * espera hasta que haya elementos disponibles. Cuando consume un elemento, notifica al 
 * productor.
 * 
 * @return NULL
 */
void *consumidor(){
    while(1){
        sleep(1); // Simula un tiempo de espera antes de intentar consumir

        pthread_mutex_lock(&condc_mutex); // Bloquea el mutex para la condición del consumidor
        while(counter <= 0){ // Si el contador está vacío, espera
            pthread_cond_signal(&condVarProd); // Notifica al productor que puede producir
            pthread_cond_wait(&condVarCons, &condc_mutex); // Espera a que haya elementos disponibles
        }
        pthread_mutex_unlock(&condc_mutex); // Desbloquea el mutex de condición del consumidor

        pthread_mutex_lock(&counter_mutex); // Bloquea el mutex para el contador
        if(counter > 0){ // Verifica que haya elementos para consumir
            printf("Soy el CONSUMIDOR %d || Contador = %d\n", pthread_self(), counter);
            counter--; // Decrementa el contador
            pthread_cond_signal(&condVarProd); // Notifica al productor que hay espacio disponible
        }
        pthread_mutex_unlock(&counter_mutex); // Desbloquea el mutex del contador
        pthread_mutex_unlock(&condc_mutex); // Desbloquea el mutex de condición del consumidor
    }
}
