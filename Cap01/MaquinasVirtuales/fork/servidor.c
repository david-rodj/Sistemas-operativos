/***********************************************************
Fecha: 24/09/2024
Autor: David Rodriguez
Materia: Sistemas operativos
Tema: Pipe named o FIFO o tubería
Tópico: Comunicación unidireccional
***********************************************************/

#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define FIFO_FILE "MYFIFO" // Nombre del archivo FIFO

/**
 * @brief Función principal del programa.
 *
 * Esta función crea un pipe FIFO y permite al programa leer mensajes
 * enviados a través de él. Los mensajes se reciben de forma continua
 * hasta que se recibe el mensaje "fin", momento en el cual el programa
 * cierra el pipe y termina la ejecución.
 *
 * @return int Devuelve 0 si el programa se ejecuta correctamente.
 */
int main() {
    int fd;                     // Descriptor de archivo para el FIFO
    char leerbuf[80];          // Buffer para almacenar el mensaje recibido
    char fin[10];              // Mensaje que indica el fin del proceso
    int final;                 // Variable para verificar si se debe finalizar el proceso
    int leer_bytes;            // Número de bytes leídos del FIFO
    
    /* Crear el FIFO si no existe */
    mknod(FIFO_FILE, S_IFIFO | 0640, 0); // Crear el archivo FIFO
    strcpy(fin, "fin");       // Copiar el mensaje de fin al buffer

    while (1) {
        fd = open(FIFO_FILE, O_RDONLY); // Abrir el FIFO para lectura
        leer_bytes = read(fd, leerbuf, sizeof(leerbuf)); // Leer del FIFO
        leerbuf[leer_bytes] = '\0'; // Terminar la cadena con un carácter nulo

        // Mostrar el mensaje recibido
        printf("Mensaje recibido: \"%s\" con %d\n", leerbuf, (int)strlen(leerbuf));
        
        final = strcmp(leerbuf, "fin"); // Comparar el mensaje recibido con "fin"
        
        // Si se recibe "fin", cerrar el FIFO y salir del bucle
        if (final == 0) {
            close(fd); // Cerrar el descriptor del FIFO
            break; // Salir del bucle
        }
    }

    return 0; // Terminar el programa
}
