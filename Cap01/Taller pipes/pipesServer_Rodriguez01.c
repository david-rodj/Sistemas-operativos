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
    char leerbuf[80];
    char fin[10];
    int final;
    int leer_bytes;
    
    /* Create the FIFO if it does not exist */
    mknod(FIFO_FILE, S_IFIFO|0640, 0);
    strcpy(fin, "FIN");
    while(1) {
       fd = open(FIFO_FILE, O_RDONLY);
       leer_bytes = read(fd, leerbuf, sizeof(leerbuf));
       leerbuf[leer_bytes] = '\0';
       printf("Mensaje recibido: \"%s\" con %d\n", leerbuf, (int)strlen(leerbuf));
       final = strcmp(leerbuf, "fin");
       if (final == 0) {
          close(fd);
          break;
       }
    }
  
  return 0;
}