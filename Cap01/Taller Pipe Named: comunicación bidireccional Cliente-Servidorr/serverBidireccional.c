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

/**
 * Invierte una cadena de caracteres.
 * 
 * Esta función toma una cadena de caracteres como parámetro y la invierte.
 * 
 * Ejemplo:
 * char cadena[] = "hola";
 * invertir_cadena(cadena);
 * printf("%s\n", cadena); // Imprime "aloh"
 * 
 * @param cadena La cadena de caracteres a invertir.
 */
void invertir_cadena(char *cadena) {
    int ultimo, limite, primero;
    char temporal;
    ultimo = strlen(cadena) - 1;
    limite = ultimo/2;
    primero = 0;

    while (primero < ultimo) {
        temporal = cadena[primero];
        cadena[primero] = cadena[ultimo];
        cadena[ultimo] = temporal;
        primero++;
        ultimo--;
    }
    return;
}

/**
 * Programa principal del servidor FIFO.
 * 
 * Este programa crea un FIFO y se queda esperando a que se escriba en él.
 * Cuando se escribe en el FIFO, se lee la cadena, se invierte y se escribe de vuelta en el FIFO.
 * El programa se detiene cuando se escribe la cadena "fin" en el FIFO.
 * 
 * @return 0 si el programa se ejecuta correctamente.
 */
int main() {
    int descriptor_archivo;
    char buffer_leido[80];
    char fin[10];
    int hasta_fin;
    int bytes_leidos;

    /* Crea el FIFO si no existe */
    mkfifo(FIFO_FILE, S_IFIFO|0640);
    strcpy(fin, "fin");
    descriptor_archivo = open(FIFO_FILE, O_RDWR);
    while(1) {
        bytes_leidos = read(descriptor_archivo, buffer_leido, sizeof(buffer_leido));
        buffer_leido[bytes_leidos] = '\0';
        printf("SERVIDOR_FIFO: Recibió cadena: \"%s\" y longitud es %d\n", buffer_leido, (int)strlen(buffer_leido));
        hasta_fin = strcmp(buffer_leido, fin);

        if (hasta_fin == 0) {
            close(descriptor_archivo);
            break;
        }
        invertir_cadena(buffer_leido);
        printf("SERVIDOR_FIFO: Enviando cadena invertida: \"%s\" y longitud es %d\n", buffer_leido, (int) strlen(buffer_leido));
        write(descriptor_archivo, buffer_leido, strlen(buffer_leido));
        /*
        sleep - Esto es para asegurarse de que el otro proceso lea este mensaje, de lo contrario este
        proceso recuperaría el mensaje
        */
        sleep(1);
    }
    return 0;
}
