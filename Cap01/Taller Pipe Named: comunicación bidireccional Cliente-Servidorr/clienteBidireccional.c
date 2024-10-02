/***********************************************************
Fecha: 01/10/2024
Autor: David Rodriguez
Materia: Sisteas operativos
Tema: Pipe named o FIFO o tuberia
Topico: Comunicacion bidireccional
***********************************************************/

#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h> 

#define FIFO_FILE "/tmp/fifo_twoway"
int main() {
    int descriptor_archivo;
    int fin_proceso;
    int longitud_cadena;
    int bytes_leidos;
    char buffer_leido[80];
    char cadena_fin[5];
    printf("CLIENTE_FIFO: Envía mensajes infinitamente, para terminar ingresa \"fin\"\n");
    descriptor_archivo = open(FIFO_FILE, O_CREAT|O_RDWR);
    strcpy(cadena_fin, "fin");

    while (1) {
        printf("Ingrese cadena: ");
        fgets(buffer_leido, sizeof(buffer_leido), stdin);
        longitud_cadena = strlen(buffer_leido);
        buffer_leido[longitud_cadena - 1] = '\0';
        fin_proceso = strcmp(buffer_leido, cadena_fin);

        //printf("fin_proceso es %d\n", fin_proceso);
        if (fin_proceso != 0) {
            write(descriptor_archivo, buffer_leido, strlen(buffer_leido));
            printf("CLIENTE_FIFO: Envió cadena: \"%s\" y longitud es %d\n", buffer_leido, (int)strlen(buffer_leido));
            bytes_leidos = read(descriptor_archivo, buffer_leido, sizeof(buffer_leido));
            buffer_leido[bytes_leidos] = '\0';
            printf("CLIENTE_FIFO: Recibió cadena: \"%s\" y longitud es %d\n", buffer_leido, (int)strlen(buffer_leido));
        } else {
            write(descriptor_archivo, buffer_leido, strlen(buffer_leido));
            printf("CLIENTE_FIFO: Envió cadena: \"%s\" y longitud es %d\n", buffer_leido, (int)strlen(buffer_leido));
            close(descriptor_archivo);
            break;
        }
    }
    return 0;
}                                       