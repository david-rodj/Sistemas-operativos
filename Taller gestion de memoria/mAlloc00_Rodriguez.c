/*********************************************************
Pontificia Universidad Javeriana
Autor: David rodriguez
Fecha: 13/08/2024
Materia: Sistemas operativos
Tema: Gestion de memoria, reserva de memoria con malloc()

Def: malloc es una función en C que reserva dinámicamente 
un bloque de memoria en el heap del tamaño especificado 
en bytes. Al llamarla, devuelve un puntero al primer byte 
del bloque reservado. Si la reserva es exitosa, el 
puntero apunta a la memoria asignada y no se inicializan 
los espacios de memoria; si falla, devuelve NULL, 
indicando que no se pudo asignar la memoria solicitada. 
Es importante liberar la memoria reservada con free() 
cuando ya no se necesite, para evitar fugas de memoria.
*********************************************************/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
  
  // Se reserva memoria para un bloque de 4 enteros
  int *bloque00 = malloc(4 * sizeof(int));
  
  // Se reserva memoria para un bloque de 15 enteros
  int *puntero = malloc(15 * sizeof(*puntero));
  
  // Se verifica que la memoria para bloque00 se haya reservado correctamente
  if (bloque00 == NULL) {
    printf("Error al reservar memoria para bloque00.\n");
    return 1; // Sale del programa con un código de error
  }
  
  // Se inicializa un bucle para llenar el bloque00
  for (int i = 0; i < 4; i++){
    // Se asigna a cada posición de bloque00 el valor del índice multiplicado por 2
    bloque00[i] = i * 2;
    
    // Se imprime el valor almacenado en cada posición del bloque00
    printf("El valor de memoria reservada bloque00[%d] = %d \n\n", i, bloque00[i]);
  }
  
  // Se verifica que la memoria para puntero se haya reservado correctamente
  if (puntero != NULL){
    // Se asigna el valor 9889 a la novena posición del bloque de memoria reservado por puntero
    *(puntero + 8) = 9889;
    
    // Se imprime el valor almacenado en la novena posición utilizando dos formas diferentes de acceso
    printf("El valor de la 9na posición de puntero es: %d \n", *(puntero + 8));
    printf("El valor de la 9na posición de puntero es: %d \n", puntero[8]);    
  } else {
    printf("Error al reservar memoria para puntero.\n");
    free(bloque00); // Libera la memoria de bloque00 antes de salir
    return 1; // Sale del programa con un código de error
  }
  
  // Se libera la memoria reservada para bloque00 y puntero
  free(bloque00);
  free(puntero);
  
  // El programa finaliza exitosamente
  return 0;
}

