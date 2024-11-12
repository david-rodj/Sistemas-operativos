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

/**
 * Constante que define el nombre del archivo FIFO para la comunicación entre procesos.
 */
#define FIFO_FILE "/tmp/fifo_twoway"

/**
 * Función principal del programa.
 * 
 * Esta función crea un archivo FIFO y se encarga de enviar y recibir cadenas de texto infinitamente hasta que se ingrese la cadena "fin".
 * 
 * @return 0 si el programa se ejecuta correctamente.
 */
int main() {
    int descriptor_archivo;
    int fin_proceso;
    int longitud_cadena;
    int bytes_leidos;
    char buffer_leido[80];
    char cadena_fin[5];

    /**
     * Mensaje de bienvenida y explicación del funcionamiento del programa.
     */
    printf("CLIENTE_FIFO: Envía mensajes infinitamente, para terminar ingresa \"fin\"\n");

    /**
     * Creación del archivo FIFO con permisos de lectura y escritura.
     */
    descriptor_archivo = open(FIFO_FILE, O_CREAT|O_RDWR);

    /**
     * Inicialización de la cadena que indica el fin del proceso.
     */
    strcpy(cadena_fin, "fin");

    /**
     * Bucle infinito para enviar y recibir cadenas de texto.
     */
    while (1) {
        printf("Ingrese cadena: ");
        fgets(buffer_leido, sizeof(buffer_leido), stdin);
        longitud_cadena = strlen(buffer_leido);
        buffer_leido[longitud_cadena - 1] = '\0';
        fin_proceso = strcmp(buffer_leido, cadena_fin);

        //printf("fin_proceso es %d\n", fin_proceso);
        if (fin_proceso != 0) {
            /**
             * Envío de la cadena ingresada por el usuario a través del archivo FIFO.
             */
            write(descriptor_archivo, buffer_leido, strlen(buffer_leido));
            printf("CLIENTE_FIFO: Envió cadena: \"%s\" y longitud es %d\n", buffer_leido, (int)strlen(buffer_leido));

            /**
             * Lectura de la respuesta del servidor a través del archivo FIFO.
             */
            bytes_leidos = read(descriptor_archivo, buffer_leido, sizeof(buffer_leido));
            buffer_leido[bytes_leidos] = '\0';
            printf("CLIENTE_FIFO: Recibió cadena: \"%s\" y longitud es %d\n", buffer_leido, (int)strlen(buffer_leido));
        } else {
            /**
             * Envío de la cadena "fin" para indicar el fin del proceso.
             */
            write(descriptor_archivo, buffer_leido, strlen(buffer_leido));
            printf("CLIENTE_FIFO: Envió cadena: \"%s\" y longitud es %d\n", buffer_leido, (int)strlen(buffer_leido));

            /**
             * Cierre del archivo FIFO.
             */
            close(descriptor_archivo);
            break;
        }
    }
    return 0;
}
