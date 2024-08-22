/********************************************************
Pontificia Universidad Javeriana
Autor: David Rodríguez
Fecha: 13/08/2024
Materia: Sistemas Operativos
Tema: Gestión de Memoria, Reserva de Memoria con `calloc()`

Def: calloc es una función en C que reserva memoria 
dinámica para una matriz de elementos, donde cada elemento 
tiene un tamaño especificado. A diferencia de malloc, 
calloc inicializa todos los bytes de la memoria asignada 
a 0. Esto es útil cuando se necesita asegurar que la 
memoria esté limpia antes de su uso, especialmente en 
estructuras de datos más complejas. La memoria reservada 
es contigua y debe liberarse con free() cuando ya no se 
necesite.
********************************************************/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
  
  // Se reservan bloques de memoria para 4, 10, y 5 enteros respectivamente, todos inicializados en 0
  int *p1 = calloc(4, sizeof(int));
  int *p2 = calloc(10, sizeof(int));
  int *p3 = calloc(5, sizeof(*p3));

  for (int i = 0; i < 4; i++)
    // Se imprime cada valor asignado en p1, se imprimira 0 ya que la memoria resevada se inicia en 0
    printf("El valor de p1 en %d es: %d \n\n", i,*(p1 + i));

  // Se recorre el bloque de p2 y se asignan valores secuenciales del 1 al 10
  for (int i = 0; i < 10; i++){
    *(p2 + i) = i;
    // Se imprime cada valor asignado en p2
    printf("El valor de p2 en %d es: %d \n\n", i,*(p2 + i));
  }

  for (int i = 0; i < 5; i++)
    // Se imprime cada valor asignado en p3, se imprimira 0 ya que la memoria resevada se inicia en 0
    printf("El valor de p3 en %d es: %d \n\n", i,*(p3 + i));
  
  // Se libera la memoria reservada para p1, p2 y p3
  free(p1);
  free(p2);
  free(p3);
  
  // El programa finaliza exitosamente
  return 0;
}
