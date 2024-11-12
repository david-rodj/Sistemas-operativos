#!/usr/bin/perl
#**************************************************************
#         		Pontificia Universidad Javeriana
#     Autor: J. Corredor
#     Fecha: Febrero 2024
#     Materia: Sistemas Operativos
#     Tema: Taller de Evaluación de Rendimiento
#     Fichero: script automatización ejecución por lotes 
#****************************************************************/

# Obtener el directorio actual y eliminar el salto de línea
$Path = `pwd`;
chomp($Path); 

# Nombre del ejecutable que se va a ejecutar
$Nombre_Ejecutable = "MM_ejecutable"; 

# Tamaños de las matrices a utilizar en las pruebas
@Size_Matriz = ("200","300"); 

# Número de hilos a utilizar en las pruebas
@Num_Hilos = (1,2); 

# Número de repeticiones para cada combinación de tamaño y hilos
$Repeticiones = 2; 

# Iterar sobre cada tamaño de matriz
foreach $size (@Size_Matriz) {
    # Iterar sobre cada número de hilos
    foreach $hilo (@Num_Hilos) {
        # Crear el nombre del archivo de salida basado en el tamaño y número de hilos
        $file = "$Path/$Nombre_Ejecutable-".$size."-Hilos-".$hilo.".dat"; 
        
        # Repetir la ejecución del programa para cada combinación
        for ($i=0; $i<$Repeticiones; $i++) {
            # Ejecutar el programa con los parámetros correspondientes y redirigir la salida al archivo
            system("$Path/$Nombre_Ejecutable $size $hilo  >> $file");
            # Imprimir el comando que se ejecutaría (actualmente comentado)
            printf("$Path/$Nombre_Ejecutable $size $hilo \n"); 
        }
        close($file); # Cerrar el archivo (no es necesario aquí, ya que no se abrió con 'open')
        $p=$p+1; # Contador de ejecuciones (no se utiliza en el resto del script)
    }
}
