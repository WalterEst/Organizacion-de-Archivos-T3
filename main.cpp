#include <stdio.h>

int ObtenerContador() {

    // Instanciamos un nuevo archivo llamado contador.txt
    FILE *contadorArchivo = fopen("contador.txt", "r");
    if (contadorArchivo == NULL) {
        return 0; // Si el archivo no existe, el contador se inicia en 0
    }
    int contador;

    fscanf(contadorArchivo, "%d", &contador);
    fclose(contadorArchivo);
    return contador;
}

// Declarar una función para actualizar el contador
void ActualizarContador(int nuevoContador) {
    FILE *contadorArchivo = fopen("contador.txt", "w");
    if (contadorArchivo == NULL) {
        printf("Error al abrir el archivo del contador.\n");
        return;
    }
    fprintf(contadorArchivo, "%d", nuevoContador);
    fclose(contadorArchivo);
}


// Declarar la función Ingresar
void Ingresar() {
    FILE *archivo = fopen("archivo.dat", "a");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }
    
    // Obtener el valor actual del contador
    int numeroFila = ObtenerContador();

    // Incrementar el contador para la siguiente inserción
    numeroFila++;

    // Declarar variables para almacenar los datos del auto
    char marca[100], modelo[100], tipo_gasolina[100], color[100];
    float motor_cilindrada;
    int cantidad_asientos, cantidad_puertas;
    
    // Solicitar al usuario que ingrese los datos del auto
    printf("Marca: ");
    scanf("%s", marca);
    printf("Modelo: ");
    scanf("%s", modelo);
    printf("Cilindrada de motor: ");
    scanf("%f", &motor_cilindrada);
    printf("Tipo de gasolina: ");
    scanf("%s", tipo_gasolina);
    printf("Cantidad de asientos: ");
    scanf("%d", &cantidad_asientos);
    printf("Cantidad de puertas: ");
    scanf("%d", &cantidad_puertas);
    printf("Color: ");
    scanf("%s", color);

    // Escribir los datos del auto en el archivo en un formato específico con el número de fila
    fprintf(archivo, "%d: %s-%s-%.1f-%s-%d-%d-%s\n", numeroFila, marca, modelo, motor_cilindrada, tipo_gasolina, cantidad_asientos, cantidad_puertas, color);
    printf("Auto ingresado con éxito.\n");

    // Actualizar el contador en el archivo
    ActualizarContador(numeroFila);

    // Cerrar el archivo
    fclose(archivo);
}


// Función para mostrar los datos de todos los autos en el archivo
void Mostrar() {
    // Abrir el archivo en modo lectura
    FILE *archivo = fopen("archivo.dat", "r");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    char linea[1000];
    // Leer y mostrar cada línea del archivo
    while (fgets(linea, sizeof(linea), archivo) != NULL) {
        printf("%s \n", linea);
    }

    // Cerrar el archivo
    fclose(archivo);
}

// Función para eliminar todos los autos del archivo
void Eliminar() {
    // Abrir el archivo en modo escritura (esto lo vaciará)
    FILE *archivo = fopen("archivo.dat", "w");
    if (archivo == NULL) {
        printf("Error al abrir el archivo en modo escritura.\n");
        return;
    }
    
    // Cerrar el archivo para vaciarlo
    fclose(archivo);
    printf("Los vehiculos han sido eliminados.\n");
}

// Función para cambiar el formato de separación en el archivo
void CambiarFormatoEnArchivo() {
    // Abrir el archivo en modo lectura y escritura
    FILE *archivo = fopen("archivo.dat", "r+");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    char formato;
    // Solicitar al usuario que ingrese el nuevo caracter de separación
    printf("Ingresa el caracter para reemplazar ('-' o '/'): ");
    scanf(" %c", &formato);

    int caracter;
    // Leer cada caracter en el archivo y reemplazar '-' o '/' por el nuevo caracter
    while ((caracter = fgetc(archivo)) != EOF) {
        if (caracter == '-' || caracter == '/') {
            fseek(archivo, -1, SEEK_CUR);
            fputc(formato, archivo);
            fseek(archivo, 0, SEEK_CUR);
        }
    }

    // Cerrar el archivo
    fclose(archivo);
    printf("Reemplazo completado.\n");
}

int main() {
    int opcion;
    do {
        printf("-------------------- CRUD DE AUTOMOVILES --------------------");
        printf("\nMenu de opciones:\n");
        printf("1. Ingresar\n");
        printf("2. Mostrar\n");
        printf("3. Eliminar\n");
        printf("4. Cambiar el formato en el archivo.dat\n");
        printf("5. Modificar (No disponible)\n");
        printf("0. Salir\n");
        printf("-------------------- CRUD DE AUTOMOVILES -------------------- \n");
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
                Eliminar();
                break;
            case 4:
                CambiarFormatoEnArchivo();
                break;
            case 5:
                printf("Funcion por agregar \n");
                break;
            case 0:
                printf("Saliendo del programa.\n");
                break;
            default:
                printf("Opcion invalida.\n");
        }
    } while (opcion != 0);

    return 0;
}
