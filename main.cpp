#include <stdio.h>

// Función para ingresar un nuevo producto de madera y guardar en el archivo.
void Ingresar() {
    FILE *archivo = fopen("archivo.dat", "a");
    char marca[100], modelo[100], motor_cilindrada[100], tipo_gasolina[100], color[100];
    printf("Marca: ");
    scanf("%s", marca);
    printf("Modelo: ");
    scanf("%s", modelo);
    printf("Cilindrada de motor: ");
    scanf("%s", motor_cilindrada);
    printf("Tipo de gasolina: ");
    scanf("%s", tipo_gasolina);

    fprintf(archivo, "%s-%s-%s-%s\n", marca, modelo, motor_cilindrada, tipo_gasolina);
    printf("Auto ingresado con exito.\n");
    fclose(archivo);
}

// Función para mostrar el contenido del archivo con el formato especificado.
void Mostrar() {
    FILE *archivo = fopen("archivo.dat", "r");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.\n");
    }

    char linea[1000]; // Suponemos que cada línea tiene un máximo de 1000 caracteres
    while (fgets(linea, sizeof(linea), archivo) != NULL) {
        printf("%s", linea);
    }

    fclose(archivo); // Cierra el archivo cuando hayas terminado de leerlo
}

// Función para eliminar todos los productos de madera en el archivo.
void Eliminar(FILE *archivo) {
    fclose(archivo);
    archivo = fopen("archivo.dat", "w");
    if (archivo == NULL) {
        printf("Error al abrir el archivo en modo escritura.\n");
        return;
    }
    printf("Todos los productos de auto han sido eliminados.\n");
}
// Función para cambiar el formato de separación entre categorías en el archivo .dat.
void CambiarFormatoEnArchivo() {
    FILE* archivo = fopen("archivo.dat", "r+");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    char formato;
    printf("Ingresa el caracter para reemplazar ('-' o '/'): ");
    scanf(" %c", &formato);  // Leemos un solo carácter

    int caracter;
    while ((caracter = fgetc(archivo)) != EOF) {
        if (caracter == '-' || caracter == '/') {
            fseek(archivo, -1, SEEK_CUR);  // Retroceder un carácter
            fputc(formato, archivo);      // Reemplazar el carácter
            fseek(archivo, 0, SEEK_CUR);   // Ajustar el puntero a la posición actual
        }
    }

    fclose(archivo);
    printf("Reemplazo completado.\n");
}

// Función para modificar una sección específica del archivo.
void Modificar(FILE *archivo) {
    int lineaModificar;
    printf("Ingrese el numero de linea que desea modificar (0 para la primera linea, 1 para la segunda, y asi sucesivamente): ");
    scanf("%d", &lineaModificar);

    if (lineaModificar < 0) {
        printf("Numero de linea no valido. Intente de nuevo.\n");
        return;
    }

    // Crear un archivo temporal para escribir los cambios.
    FILE *tempArchivo = fopen("temp.dat", "w");
    rewind(archivo);

    char linea[256];
    int lineaActual = 0;

    while (fgets(linea, sizeof(linea), archivo)) {
        if (lineaActual == lineaModificar) {
            char marca[100], modelo[100], motor_cilindrada[100], tipo_gasolina[100], color[100];
            printf("Marca: ");
            scanf("%s", marca);
            printf("Modelo: ");
            scanf("%s", modelo);
            printf("Cilindrada de motor: ");
            scanf("%s", motor_cilindrada);
            printf("Tipo de gasolina: ");
            scanf("%s", tipo_gasolina);

            fprintf(tempArchivo, "%s-%s-%s-%s\n", marca, modelo,  motor_cilindrada, tipo_gasolina);
            printf("Linea modificada con exito.\n");
        } else {
            fputs(linea, tempArchivo);
        }
        lineaActual++;
    }
    fclose(tempArchivo);
    fclose(archivo);

    // Reemplazar el archivo original con el archivo temporal.
    remove("archivo.dat");
    rename("temp.dat", "archivo.dat");
    CambiarFormatoEnArchivo();
}

int main() {
    FILE *archivo = fopen("archivo.dat", "a+");
    if (archivo == NULL) {
        printf("Error al abrir o crear el archivo.\n");
        return 1;
    }

    char formato = '-';

    int opcion;
    do {
        printf("\nMenu de opciones:\n");
        printf("1. Ingresar\n");
        printf("2. Mostrar\n");
        printf("3. Eliminar\n");
        printf("4. Cambiar el formato en el archivo .dat\n");
        printf("5. Modificar\n");
        printf("0. Salir\n");
        printf("Ingrese su eleccion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                Ingresar();
                break;
            case 2:
                Mostrar();
                break;
            case 3:
                Eliminar(archivo);
                break;
            case 4:
                CambiarFormatoEnArchivo();
                break;
            case 5:
                Modificar(archivo);
                break;
            case 0:
                printf("Saliendo del programa.\n");
                break;
            default:
                printf("Opcion no valida. Intente de nuevo.\n");
        }
    } while (opcion != 0);

    fclose(archivo);
    return 0;
}