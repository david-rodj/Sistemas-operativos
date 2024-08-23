/**********************************************************************
Pontificia Universidad Javeriana
Autor: David Rodríguez
Fecha: 22/08/2024
Materia: Sistemas Operativos
Tema: Gestión de Memoria, Redimensionamiento de Memoria con `realloc()`

Def: realloc es una función de la biblioteca estándar de C que se 
utiliza para cambiar el tamaño de un bloque de memoria previamente 
asignado. Esta función puede aumentar o reducir el tamaño del bloque, 
preservando el contenido original hasta el mínimo entre el tamaño 
antiguo y el nuevo. Si el nuevo tamaño es mayor, la memoria adicional 
no está inicializada. Si ptr es NULL, realloc actúa como malloc, 
asignando un nuevo bloque de memoria. Si el tamaño es cero y ptr no es 
NULL, actúa como free. En caso de que la memoria sea reubicada, realloc
se encarga de liberar la memoria original.
***********************************************************************/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
  
  // Se reserva memoria para un bloque de 5 enteros
  int *arreglo = malloc(5 * sizeof(int));
  
  // Se verifica que la memoria se haya reservado correctamente
  if (arreglo == NULL) {
    printf("Error al reservar memoria.\n");
    return 1;
  }else
    printf("Se asigno la memoria al arreglo\n\n);
  
  // Se asignan valores a las primeras 5 posiciones del bloque de memoria de 1 a 5
  for (int i = 0; i < 5; i++){
    arreglo[i] = i + 1;
    //Se imprimen los valores del arreglo en i
    printf("Valor del arreglo[%d] = %d\n", i, arreglo[i]);
  }
  
  // Se redimensiona el bloque de memoria para que tenga 15 enteros, o sea 10 enteros mas
  arreglo = realloc(arreglo, 15 * sizeof(int));
  
  // Se verifica que la memoria se haya redimensionado correctamente
  if (arreglo == NULL) {
    printf("Error al redimensionar memoria.\n");
    return 1;
  }else
    printf("\nSe redimensiono la memoria del arreglo\n\n);
  
  // Se asignan valores a las nuevas posiciones del bloque de memoria
  for (int i = 5; i < 15; i++){
    arreglo[i] = (i + 1) * 2;
     printf("Valor del arreglo[%d] = %d\n", i, arreglo[i]);
  }
  
  // Se libera la memoria redimensionada
  free(arreglo);
  
  // El programa finaliza exitosamente
  return 0;
}
