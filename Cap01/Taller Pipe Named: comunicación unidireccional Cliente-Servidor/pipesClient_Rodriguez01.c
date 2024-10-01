/***********************************************************
Fecha: 24/09/2024
Autor: David Rodriguez
Materia: Sisteas operativos
Tema: Pipe named o FIFO o tuberia
Topico: Comunicacion unidireccional
***********************************************************/

#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define FIFO_FILE "MYFIFO"
int main() {
    int fd;
    int fin_proceso;
    int tamMensaje;
    char leerbuf[80];
    char fin_men[5];
    printf("FIFO_CLIENT: Mensajes recibidos, infinitamente, para finalizar \"fin\" \n");
    fd = open(FIFO_FILE, O_CREAT|O_WRONLY);
    strcpy(fin_men, "end");
 
    while (1) {
       printf("Ingrese mensaje: ");
       fgets(leerbuf, sizeof(leerbuf), stdin);
       tamMensaje = strlen(leerbuf);
       leerbuf[tamMensaje - 1] = '\0';
       fin_proceso = strcmp(leerbuf, fin_men);
 
       //printf("end_process is %d\n", end_process);
       if (fin_proceso != 0) {
          write(fd, leerbuf, strlen(leerbuf));
          printf("Mensaje enviado: \"%s\" con %d\n", leerbuf, (int)strlen(leerbuf));
       } else {
          write(fd, leerbuf, strlen(leerbuf));
          printf("Mensaje enviado: \"%s\" con %d\n", leerbuf, (int)strlen(leerbuf));
          close(fd);
          break;
       }
    }
    return 0;
}