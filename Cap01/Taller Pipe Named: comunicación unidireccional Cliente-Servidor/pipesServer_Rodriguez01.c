/***********************************************************
Fecha: 24/09/2024
Autor: David Rodriguez
Materia: Sisteas operativos
Tema: Pipe named o FIFO o tuberia
Topico: Comunicacion unidireccional
***********************************************************/

include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

/**
 * @def FIFO_FILE
 * @brief Nombre del archivo FIFO.
 */
#define FIFO_FILE "MYFIFO"

/**
 * @brief Función principal del programa.
 * 
 * Crea un archivo FIFO si no existe y se queda en un bucle infinito leyendo mensajes
 * del archivo FIFO hasta que se reciba el mensaje "fin".
 * 
 * @return int 0 si el programa se ejecuta correctamente.
 */
int main() {
    int fd; /**< Descriptor de archivo del archivo FIFO. */
    char leerbuf[80]; /**< Buffer para leer mensajes del archivo FIFO. */
    char fin[10]; /**< Cadena que contiene el mensaje "FIN". */
    int final; /**< Variable para almacenar el resultado de la comparación de cadenas. */
    int leer_bytes; /**< Número de bytes leídos del archivo FIFO. */
    
    /* Create the FIFO if it does not exist */
    /**
     * @brief Crea el archivo FIFO si no existe.
     * 
     * Utiliza la función mknod para crear el archivo FIFO con permisos de lectura y escritura
     * para el propietario y grupo, y permisos de lectura para otros.
     */
    mknod(FIFO_FILE, S_IFIFO|0640, 0);
    
    /**
     * @brief Copia el mensaje "FIN" en la cadena fin.
     */
    strcpy(fin, "fin");
    
    /**
     * @brief Bucle infinito para leer mensajes del archivo FIFO.
     * 
     * Se queda en este bucle hasta que se reciba el mensaje "fin".
     */
    while(1) {
       /**
        * @brief Abre el archivo FIFO en modo de solo lectura.
        */
       fd = open(FIFO_FILE, O_RDONLY);
       
       /**
        * @brief Lee un mensaje del archivo FIFO.
        * 
        * Utiliza la función read para leer un mensaje del archivo FIFO y almacena el número
        * de bytes leídos en la variable leer_bytes.
        */
       leer_bytes = read(fd, leerbuf, sizeof(leerbuf));
       
       /**
        * @brief Agrega el carácter nulo al final del buffer para convertirlo en una cadena.
        */
       leerbuf[leer_bytes] = '\0';
       
       /**
        * @brief Imprime el mensaje recibido y su longitud.
        */
       printf("Mensaje recibido: \"%s\" con %d\n", leerbuf, (int)strlen(leerbuf));
       
       /**
        * @brief Compara el mensaje recibido con el mensaje "fin".
        * 
        * Utiliza la función strcmp para comparar el mensaje recibido con el mensaje "fin"
        * y almacena el resultado en la variable final.
        */
       final = strcmp(leerbuf, "fin");
       
       /**
        * @brief Verifica si el mensaje recibido es "fin".
        * 
        * Si el mensaje recibido es "fin", cierra el descriptor de archivo y sale del bucle.
        */
       if (final == 0) {
          close(fd);
          break;
       }
    }
  
  return 0;
}