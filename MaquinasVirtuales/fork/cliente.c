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
 * Esta función crea un pipe FIFO y permite al usuario enviar mensajes
 * a través de él. Los mensajes se envían de forma continua hasta que
 * el usuario ingresa "fin", momento en el cual el programa cierra el pipe
 * y termina la ejecución.
 *
 * @return int Devuelve 0 si el programa se ejecuta correctamente.
 */
int main() {
    int fd;                     // Descriptor de archivo para el FIFO
    int fin_proceso;           // Variable para verificar si se debe finalizar el proceso
    int tamMensaje;            // Tamaño del mensaje ingresado
    char leerbuf[80];          // Buffer para almacenar el mensaje ingresado
    char fin_men[5];          // Mensaje que indica el fin del proceso

    printf("FIFO_CLIENT: Mensajes recibidos, infinitamente, para finalizar \"fin\" \n");

    // Abrir el FIFO para escritura, creándolo si no existe
    fd = open(FIFO_FILE, O_CREAT | O_WRONLY);
    strcpy(fin_men, "fin");    // Copiar el mensaje de fin al buffer

    while (1) {
        printf("Ingrese mensaje: ");
        fgets(leerbuf, sizeof(leerbuf), stdin); // Leer el mensaje del usuario
        tamMensaje = strlen(leerbuf); // Obtener el tamaño del mensaje
        leerbuf[tamMensaje - 1] = '\0'; // Reemplazar el salto de línea por el carácter nulo

        fin_proceso = strcmp(leerbuf, fin_men); // Comparar el mensaje ingresado con "fin"

        // Si el mensaje no es "fin", se escribe en el FIFO
        if (fin_proceso != 0) {
            write(fd, leerbuf, strlen(leerbuf)); // Enviar el mensaje al FIFO
            printf("Mensaje enviado: \"%s\" con %d\n", leerbuf, (int)strlen(leerbuf));
        } else {
            // Si el mensaje es "fin", se envía y se cierra el FIFO
            write(fd, leerbuf, strlen(leerbuf)); // Enviar el mensaje de fin al FIFO
            printf("Mensaje enviado: \"%s\" con %d\n", leerbuf, (int)strlen(leerbuf));
            close(fd); // Cerrar el descriptor del FIFO
            break; // Salir del bucle
        }
    }
    return 0; // Terminar el programa
}
