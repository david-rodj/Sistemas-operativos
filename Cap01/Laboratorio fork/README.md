# Proyecto de Creación de Procesos en C

Este repositorio contiene un programa en C que demuestra la creación de procesos hijos utilizando la función `fork()`. El programa crea un número determinado de procesos hijos en un bucle, mostrando información sobre cada uno de ellos.

## Descripción del Código

El archivo `fork_procesos.c` implementa un programa que permite al usuario especificar cuántos procesos hijos desea crear. Cada vez que se llama a la función `fork()`, se crea un nuevo proceso, y el programa imprime un mensaje indicando si el proceso es un hijo o un padre.

### Funciones Principales

- **creacion_fork(int linea)**: 
  - Crea un nuevo proceso hijo utilizando `fork()`.
  - Imprime un mensaje indicando si el proceso creado es un hijo o un padre, junto con el ID del proceso.
  
- **main(int argc, char *argv[])**: 
  - Función principal del programa.
  - Verifica que se haya pasado un argumento que indique el número de procesos a crear.
  - Llama a `creacion_fork` en un bucle para crear el número especificado de procesos.

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
