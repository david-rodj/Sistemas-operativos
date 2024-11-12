# Proyecto de Vector Dinámico en C

Este proyecto implementa una estructura de datos de vector dinámico en C, que permite la creación de vectores que se pueden redimensionar de manera automática conforme se añaden o eliminan elementos. El proyecto incluye los siguientes archivos:

- **dinamiclib.c**: Implementación de las funciones del vector dinámico.
- **dinamiclib.h**: Definición del vector dinámico y sus funciones.
- **modularMem_Rodriguez01.c**: Programa principal que utiliza la biblioteca `dinamiclib` para demostrar su funcionalidad.
- **Makefile**: Archivo que gestiona la compilación del proyecto.

## Compilación del Proyecto

Para compilar este proyecto, utiliza el `Makefile` incluido. A continuación, se explica cómo compilar y ejecutar el proyecto paso a paso.

### Prerrequisitos

Asegúrate de tener instalado `gcc` en tu sistema. 

Descarga el proyecto en tu maquina, o si gustas y tienes `git`, clona este repositorio.

Escribe este comando en tu consola:
```
make
```

Esto generará un archivo ejecutable llamado `modularMem_Rodriguez01`. Para ejecutar el programa digita:
```
./modularMem_Rodriguez01
```

## Explicacón del Makefile

```makefile
GCC = gcc
FLAGS = -c

PROGS = modularMem_Rodriguez01

modularMem_Rodriguez01:
		$(GCC) $(FLAGS) dinamiclib.c
		$(GCC) dinamiclib.o $@.c -o $@
		
clear:
		$(RM) $(PROGS) *.o
```

**GCC = gcc**: Define que el compilador a utilizar es ``gcc``.

**FLAGS = -c**: La bandera ``-c`` indica que queremos compilar el archivo ``.c`` en un archivo objeto ``(.o)``, pero sin enlazarlo aún.

**PROGS = modularMem_Rodriguez01**: Especifica el nombre del programa o ejecutable que queremos generar.

**\$
(GCC) \$
(FLAGS) dinamiclib.c**: Compila el archivo `dinamiclib.c` y genera un archivo objeto `dinamiclib.o`.

**\$
(GCC) dinamiclib.o \$
@.c -o \$
@**: Enlaza el archivo objeto `dinamiclib.o` con el archivo fuente `modularMem_Rodriguez01.c` (representado por `$@`), generando el ejecutable `modularMem_Rodriguez01`.

**clear**: Este objetivo elimina los archivos generados durante la compilación (archivos ``.o`` y el ejecutable). El comando ``$(RM)`` es una variable que ejecuta el comando de eliminación de archivos, lo cual limpia el directorio de los archivos compilados.
