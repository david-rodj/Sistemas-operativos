/********************************************************
Pontificia Universidad Javeriana
Autor: David rodriguez
Fecha: 13/08/2024
Materia: Sistemas operativos
Tema: Gestion de memoria, reserva de memoria con calloc()
Def: La funcion calloc reserva un espacio de memoria, 
los espacios son de igual tamaño y de memoria contigua,
la asignacion es dinamica y util para estructuras
complejas de datos, la memoeria se inicializa en 0
********************************************************/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
  
  int *p1 = calloc(4, sizeof(int));
  int *p2 = calloc(10, sizeof(int));
  int *p3 = calloc(5, sizeof(*p3));

  
  
  for (int i = 0; i < 10; i++){
    *(p2+i)=i;
    printf("El valor de la secuencia es: %d \n\n",*(p2+i));
    
  }
  
  free(p1);
  free(p2);
  free(p3);
  return 0;
}
