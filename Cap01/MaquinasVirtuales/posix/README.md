# Proyecto de Hilos en C

Este repositorio contiene dos programas en C que demuestran el uso de hilos y sincronización en un entorno de programación concurrente. Los programas implementan diferentes conceptos de programación con hilos, incluyendo la creación de hilos y un modelo de productor-consumidor.

## Contenido del Repositorio

- `code00.c`: Implementación de un programa que crea múltiples hilos, cada uno ejecutando una función que imprime un número de trabajo.
- `code01.c`: Implementación de un modelo productor-consumidor utilizando hilos, donde los productores incrementan un contador compartido y los consumidores lo decrementan, utilizando mutexes y variables de condición para la sincronización.

# Guia de compilación y ejecución del proyecto
En este archivo estará el paso a paso para compilar y ejecutar el proyecto en su totalidad, espero sea de de gran ayuda.


## Instalar Compilador g++ con MinGW para Windows (Puedes saltarte este paso si ya lo tienes o usas un sistema basado en Unix)
Para compilar este proyecto recomiendo `g++`, así que lo tendremos que instalar siguiendo la guia de [MSYS2](https://www.msys2.org/), este te instalara tanto `g++` como `gcc` y `gdb`.


## Compilación
Para compilar el proyecto, abriras la consola de tu preferencia, digitaras el siguiente comando remplazando los parametros segun tu necesidad:

```bash
g++ [nombre del fichero(s) a compilar (.c, .cpp y .cxx)] -o [nombre del ejecutable]
```

## Ejecución
Para ejecutar el proyecto, digitaras el siguiente comando en la consola:

```bash
./[nombre del ejecutable] 
```
