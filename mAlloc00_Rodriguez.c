/********************************************************
Pontificia Universidad Javeriana
Autor: David rodriguez
Fecha: 13/08/2024
Materia: Sistemas operativos
Tema: Gestion de memoria, reserva de memoria con malloc()
Def: La funcion malloc reserva un espacio de memoria y
retorna un puntero hacia el espacio reservado
********************************************************/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
  
  int *bloque00 = malloc(4*sizeof(int));
  int *puntero = malloc(15*sizeof(*puntero));
  
  
  for (int i = 0; i < 4; i++){
    bloque00[i] = i*2;
    printf("El valor de memoria reservada bloque00[%d]= %d \n\n",i,bloque00[i]);
    
  }
  
  if(puntero !=NULL){
    *(puntero+8)=9889;
    printf("El valor de la 9na posicion de puntero es: %d \n", *(puntero+8));
    printf("El valor de la 9na posicion de puntero es: %d \n", puntero[8]);    
  }
  
  
  return 0;
}
