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
    // Abrir el archivo original en modo lectura
    FILE *archivoLectura = fopen("archivo.dat", "r");
    if (archivoLectura == NULL) {
        printf("No se pudo abrir el archivo para lectura.\n");
        return;
    }

    // Abrir un archivo temporal en modo escritura
    FILE *archivoTemporal = fopen("temporal.dat", "w");
    if (archivoTemporal == NULL) {
        printf("No se pudo abrir el archivo temporal.\n");
        fclose(archivoLectura);
        return;
    }

    int idAEliminar;
    printf("Ingrese el ID del automóvil que desea eliminar: ");
    scanf("%d", &idAEliminar);

    int idAutomovil;
    char linea[1000]; // Suponemos que cada línea en el archivo tiene un máximo de 1000 caracteres

    while (fgets(linea, sizeof(linea), archivoLectura) != NULL) {
        sscanf(linea, "%d", &idAutomovil);

        if (idAutomovil == idAEliminar) {
            printf("El automóvil con el ID %d ha sido eliminado.\n", idAEliminar);
        } else {
            fprintf(archivoTemporal, "%s", linea);
        }
    }

    // Cerrar los archivos
    fclose(archivoLectura);
    fclose(archivoTemporal);

    // Eliminar el archivo original
    if (remove("archivo.dat") != 0) {
        printf("Error al eliminar el archivo original.\n");
        return;
    }

    // Renombrar el archivo temporal
    if (rename("temporal.dat", "archivo.dat") != 0) {
        printf("Error al renombrar el archivo temporal.\n");
        return;
    }
}

// Función para modificar un automóvil por su ID
void Modificar() {
    FILE *archivoLectura = fopen("archivo.dat", "r");
    if (archivoLectura == NULL) {
        printf("No se pudo abrir el archivo para lectura.\n");
        return;
    }

    FILE *archivoTemporal = fopen("temporal.dat", "w");
    if (archivoTemporal == NULL) {
        printf("No se pudo abrir el archivo temporal.\n");
        fclose(archivoLectura); // Cerrar el archivo de lectura si no se pudo abrir el temporal
        return;
    }

    int idAModificar;
    printf("Ingrese el ID del automóvil que desea modificar: ");
    scanf("%d", &idAModificar);

    int idAutomovil;
    char linea[1000];

    while (fgets(linea, sizeof(linea), archivoLectura) != NULL) {
        sscanf(linea, "%d", &idAutomovil);

        if (idAutomovil == idAModificar) {
            printf("El automóvil con el ID %d ha sido encontrado.\n", idAModificar);

            // Solicitar al usuario que ingrese los datos modificados
            char marca[100], modelo[100], tipo_gasolina[100], color[100];
            float motor_cilindrada;
            int cantidad_asientos, cantidad_puertas;

            printf("Nueva Marca: ");
            scanf("%s", marca);
            printf("Nuevo Modelo: ");
            scanf("%s", modelo);
            printf("Nueva Cilindrada de motor: ");
            scanf("%f", &motor_cilindrada);
            printf("Nuevo Tipo de gasolina: ");
            scanf("%s", tipo_gasolina);
            printf("Nueva Cantidad de asientos: ");
            scanf("%d", &cantidad_asientos);
            printf("Nueva Cantidad de puertas: ");
            scanf("%d", &cantidad_puertas);
            printf("Nuevo Color: ");
            scanf("%s", color);

            // Escribir los datos modificados en el archivo temporal
            fprintf(archivoTemporal, "%d: %s-%s-%.1f-%s-%d-%d-%s\n", idAModificar, marca, modelo, motor_cilindrada, tipo_gasolina, cantidad_asientos, cantidad_puertas, color);
            printf("Automóvil modificado con éxito.\n");
        } else {
            // Si no es el automóvil a modificar, simplemente copiar la línea al archivo temporal
            fprintf(archivoTemporal, "%s", linea);
        }
    }

    fclose(archivoLectura);
    fclose(archivoTemporal);

    if (remove("archivo.dat") != 0) {
        printf("Error al eliminar el archivo original.\n");
        return;
    }

    if (rename("temporal.dat", "archivo.dat") != 0) {
        printf("Error al renombrar el archivo temporal.\n");
        return;
    }
}

// Función para cambiar el formato de separación en el archivo
void CambiarFormatoEnArchivo() {
    // Abrir el archivo en modo lectura y escritura
    FILE *archivo = fopen("archivo.dat", "r+");
    if (archivo == NULL) {
        printf("El archivo no se puede abrir.\n");
        return;
    }

    char formato;
    // Solicitar al usuario que ingrese el nuevo caracter de separación
    printf("Ingresa separador ('-' o '/' o ';' o ':'): ");
    scanf(" %c", &formato);

    int caracter;
    // Leer cada caracter en el archivo y reemplazar '-' o '/' por el nuevo caracter
    while ((caracter = fgetc(archivo)) != EOF) {
        if (caracter == '-' || caracter == '/' || caracter == ';' || caracter == ':') {
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
        printf("4. Modificar\n");
        printf("5. Cambiar el formato en el archivo.dat\n");
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
                Modificar();
                break;
            case 5:
                CambiarFormatoEnArchivo();
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