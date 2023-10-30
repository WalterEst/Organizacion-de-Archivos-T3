#include <stdio.h>
#include <stdlib.h>

FILE archivo;

int menuOpciones(){

    // Desplegamos el menu de opciones
    printf("Seleccione la opcion deseada: ");
    printf("1.- Insertar vehiculo");
    printf("2.- Mostrar vehiculos");
    printf("3.- Eliminar vehiculos");
    printf("4.- Modificar formato");
    printf("5.- Modificar vehiculo");

    return 0;
}



void crearArchivo(const char* nombreArchivo) {
    // Intentar abrir el archivo en modo lectura
    FILE* archivo = fopen(nombreArchivo, "r");
    
    // Si el archivo no existe, fopen devolverá NULL
    if (archivo == NULL) {
        // El archivo no existe, así que lo creamos
        archivo = fopen(nombreArchivo, "w");
        
        if (archivo != NULL) {
            printf("Archivo '%s' creado con éxito.\n", nombreArchivo);
            fclose(archivo); // Cerrar el archivo después de crearlo
        } else {
            printf("No se pudo crear el archivo '%s'.\n", nombreArchivo);
        }
    } else {
        // El archivo ya existe, así que no hacemos nada
        printf("El archivo '%s' ya existe. No se creó uno nuevo.\n", nombreArchivo);
        fclose(archivo); // Cerrar el archivo que se abrió en modo lectura
    }
}

int main() {
    const char* nombreArchivo = "miarchivo.txt";
    crearArchivo(nombreArchivo);
    return 0;
}