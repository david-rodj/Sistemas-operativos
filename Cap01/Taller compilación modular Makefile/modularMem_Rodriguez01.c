/******************************************************************
Pontificia Universidad Javeriana
Autor: David Rodríguez
Fecha: 27/08/2024
Materia: Sistemas operativos
Tema: Compilación modular

Def: Este código presenta una implementación básica de un vector 
dinámico en C, junto con la compilación modular usando bibliotecas. 
El propósito principal es proporcionar una estructura de datos 
flexible y eficiente para gestionar una colección de elementos de 
tamaño variable.

La implementación del vector dinámico permite al usuario:
1. Inicializar un vector con una capacidad inicial.
2. Redimensionar el vector dinámicamente cuando sea necesario.
3. Añadir, obtener, modificar y eliminar elementos en el vector.
4. Liberar los recursos de memoria asociados al vector.

El código demuestra conceptos clave como la gestión dinámica de 
memoria, el redimensionamiento de arreglos, y el uso de punteros 
genéricos. Estas técnicas son esenciales para la creación de 
estructuras de datos que requieren ajustes dinámicos en su tamaño 
y para una gestión eficiente de los recursos de memoria en 
aplicaciones en C.

El `Makefile` incluido facilita la compilación modular del proyecto, 
permitiendo compilar los archivos fuente en objetos y enlazarlos en 
un ejecutable final. También incluye un objetivo para limpiar los 
archivos generados durante el proceso de compilación.
*******************************************************************/


#include <stdio.h>
#include <stdlib.h>

#include "dinamiclib.h"

/* Función principal */
int main() {
    int i;
    vectorDinamico editor;  // Declara una variable de tipo vectorDinamico

    vectorInicio(&editor);  // Inicializa el vector

    resizeVector(&editor, 10);  // Redimensiona el vector a capacidad 10

    // Añade varios elementos al vector
    addVector(&editor, "Hola");
    addVector(&editor, "Profesional");
    addVector(&editor, "en");
    addVector(&editor, "Formación");
    addVector(&editor, "en");
    addVector(&editor, "Ingeniería");

    // Imprime todos los elementos del vector
    for (i = 0; i < totalVector(&editor); i++)
        printf("%s ", (char *) getVector(&editor, i));

    printf("\n\n");

    // Borra los últimos elementos del vector hasta el primero
    while (i > 1) {
        borrarVector(&editor, i);
        i--;
    }

    // Modifica un elemento y añade uno nuevo
    setVector(&editor, 1, "Buenos");
    addVector(&editor, "Días");

    printf("\n\n");

    // Imprime todos los elementos del vector después de las modificaciones
    for (i = 0; i < totalVector(&editor); i++)
        printf("%s ", (char *) getVector(&editor, i));

    // Libera la memoria utilizada por el vector
    freeVector(&editor);

    return 0;
}
