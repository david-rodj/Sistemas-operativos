/*****************************************************************************
*Nombre grupo: Time Quantum
*Fecha: 24/09/2024
*Tema: Taller Fork
*Descripcion: Aplicar los conceptos de procesos y comunicación entre procesos.
*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * @brief Lee un arreglo de enteros desde un archivo.
 * 
 * Esta función lee un arreglo de enteros desde un archivo y devuelve un puntero al arreglo leído.
 * 
 * @param archivo Ruta del archivo que contiene el arreglo.
 * @param n Tamaño del arreglo.
 * @return Puntero al arreglo leído.
 */
int* leer_arreglo(const char* archivo, int n) {
    // Abrimos el archivo en modo de lectura
    FILE* file = fopen(archivo, "r");
    if (file == NULL) {
        // Si no se puede abrir el archivo, mostramos un error y salimos
        perror("Error al abrir el archivo");
        exit(EXIT_FAILURE);
    }

    // Asignamos memoria para el arreglo
    int* arreglo = (int*) malloc(n * sizeof(int));
    if (arreglo == NULL) {
        // Si no se puede asignar memoria, mostramos un error y salimos
        perror("Error al asignar memoria");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    // Leemos el arreglo desde el archivo
    for (int i = 0; i < n; i++) {
        if (fscanf(file, "%d", &arreglo[i]) != 1) {
            // Si no se puede leer el archivo, mostramos un error y salimos
            perror("Error al leer el archivo");
            free(arreglo);
            fclose(file);
            exit(EXIT_FAILURE);
        }
    }

    // Cerramos el archivo
    fclose(file);
    return arreglo;
}

/**
 * @brief Calcula la suma de un arreglo de enteros.
 * 
 * Esta función calcula la suma de un arreglo de enteros y devuelve el resultado.
 * 
 * @param arreglo Puntero al arreglo.
 * @param n Tamaño del arreglo.
 * @return Suma del arreglo.
 */
int calcular_suma(int* arreglo, int n) {
    int suma = 0;
    for (int i = 0; i < n; i++) {
        suma += arreglo[i];
    }
    return suma;
}

int main(int argc, char* argv[]) {
    // Verificamos que se hayan proporcionado los argumentos correctos
    if (argc != 5) {
        fprintf(stderr, "Uso: %s N1 archivo00 N2 archivo01\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Convertimos los argumentos a enteros
    int N1 = atoi(argv[1]);
    int N2 = atoi(argv[3]);

    // Leemos los arreglos desde los archivos
    int* arregloA = leer_arreglo(argv[2], N1);
    int* arregloB = leer_arreglo(argv[4], N2);

    // Creamos las tuberías para la comunicación entre procesos
    int pipeA[2], pipeB[2], pipeC[2];

    if (pipe(pipeA) == -1 || pipe(pipeB) == -1 || pipe(pipeC) == -1) {
        // Si no se pueden crear las tuberías, mostramos un error y salimos
        perror("Error al crear las tuberías");
        exit(EXIT_FAILURE);
    }

    // Creamos los procesos hijos
    pid_t pid1, pid2, pid3;

    pid1 = fork();
    if (pid1 == 0) { // Primer hijo
        // Cerramos las tuberías que no se utilizan en este proceso
        close(pipeA[0]); // Cierra el lado de lectura de la tubería
        close(pipeB[0]);
        close(pipeB[1]);
        close(pipeC[0]);
        close(pipeC[1]);

        // Calculamos la suma del arreglo A
        int sumaA = calcular_suma(arregloA, N1);
        if (write(pipeA[1], &sumaA, sizeof(int)) == -1) {
            // Si no se puede escribir en la tubería, mostramos un error y salimos
            perror("Error al escribir en pipeA");
            exit(EXIT_FAILURE);
        }
        close(pipeA[1]);

        // Liberamos la memoria asignada para los arreglos
        free(arregloA);
        free(arregloB);
        exit(0);
    }

    pid2 = fork();
    if (pid2 == 0) { // Segundo hijo
        // Cerramos las tuberías que no se utilizan en este proceso
        close(pipeA[1]);
        close(pipeA[0]);
        close(pipeB[0]);
        close(pipeC[0]);
        close(pipeC[1]);

        // Calculamos la suma del arreglo B
        int sumaB = calcular_suma(arregloB, N2);
        if (write(pipeB[1], &sumaB, sizeof(int)) == -1) {
            // Si no se puede escribir en la tubería, mostramos un error y salimos
            perror("Error al escribir en pipeB");
            exit(EXIT_FAILURE);
        }
        close(pipeB[1]);

        // Liberamos la memoria asignada para los arreglos
        free(arregloA);
        free(arregloB);
        exit(0);
    }

    pid3 = fork();
    if (pid3 == 0) { // Nieto
        // Cerramos las tuberías que no se utilizan en este proceso
        close(pipeA[1]);
        close(pipeB[1]);
        close(pipeC[0]);

        // Calculamos la suma total
        int sumaA = calcular_suma(arregloA, N1);
        int sumaB = calcular_suma(arregloB, N2);

        int sumaTotal = sumaA + sumaB;
        if (write(pipeC[1], &sumaTotal, sizeof(int)) == -1) {
            // Si no se puede escribir en la tubería, mostramos un error y salimos
            perror("Error al escribir en pipeC");
            exit(EXIT_FAILURE);
        }

        close(pipeA[0]);
        close(pipeB[0]);
        close(pipeC[1]);

        // Liberamos la memoria asignada para los arreglos
        free(arregloA);
        free(arregloB);
        exit(0);
    }

    // Proceso padre
    close(pipeA[1]);
    close(pipeB[1]);
    close(pipeC[1]);

    int sumaA, sumaB, sumaTotal;
    if (read(pipeA[0], &sumaA, sizeof(int)) == -1) {
        // Si no se puede leer de la tubería, mostramos un error y salimos
        perror("Error al leer pipeA en el padre");
        exit(EXIT_FAILURE);
    }
    if (read(pipeB[0], &sumaB, sizeof(int)) == -1) {
        // Si no se puede leer de la tubería, mostramos un error y salimos
        perror("Error al leer pipeB en el padre");
        exit(EXIT_FAILURE);
    }
    if (read(pipeC[0], &sumaTotal, sizeof(int)) == -1) {
        // Si no se puede leer de la tubería, mostramos un error y salimos
        perror("Error al leer pipeC en el padre");
        exit(EXIT_FAILURE);
    }

    // Mostramos los resultados
    printf("Suma de A: %d\n", sumaA);
    printf("Suma de B: %d\n", sumaB);
    printf("Suma Total: %d\n", sumaTotal);

    close(pipeA[0]);
    close(pipeB[0]);
    close(pipeC[0]);

    // Esperamos a los hijos
    wait(NULL);
    wait(NULL);
    wait(NULL);

    // Liberamos la memoria asignada para los arreglos
    free(arregloA);
    free(arregloB);

    return 0;
}