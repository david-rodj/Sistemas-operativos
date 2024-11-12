# Proyecto de Cálculo de Matrices

Este repositorio contiene herramientas para calcular matrices cuadradas de tamaño N utilizando dos enfoques diferentes: un método clásico y un método transpuesto. Los programas están escritos en C y se pueden ejecutar automáticamente utilizando un script en Perl.

## Contenido del Repositorio

- `mm_clasico.c`: Implementación del cálculo de matrices utilizando el método clásico.
- `mm_transpuesta.c`: Implementación del cálculo de matrices utilizando el método transpuesto.
- `lanza.pl`: Script en Perl que automatiza la ejecución de los programas en C.

# Guia de compilación y ejecución del proyecto
En este archivo estará el paso a paso para compilar y ejecutar el proyecto en su totalidad, espero sea de de gran ayuda.


## Instalar Compilador g++ con MinGW para Windows (Puedes saltarte este paso si ya lo tienes o usas un sistema basado en Unix)
Para compilar este proyecto recomiendo `g++`, así que lo tendremos que instalar siguiendo la guia de [MSYS2](https://www.msys2.org/), este te instalara tanto `g++` como `gcc` y `gdb`.


## Compilación
Para compilar el proyecto, abriras la consola de tu preferencia, digitaras el siguiente comando remplazando los parametros segun tu necesidad:

```bash
g++ [nombre del fichero(s) a compilar (.cpp y .cxx)] -o [nombre del ejecutable]
```

## Ejecución
Para ejecutar el proyecto, digitaras el siguiente comando en la consola:

```bash
./[nombre del ejecutable] 
```

