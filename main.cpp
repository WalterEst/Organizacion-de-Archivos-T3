#include <stdio.h>

int ObtenerContador() {

    FILE *contadorArchivo = fopen("contador.txt", "r");
    if (contadorArchivo == NULL) {
    }
    int contador;

    fscanf(contadorArchivo, "%d", &contador);
    fclose(contadorArchivo);
    return contador;
}

void ActualizarContador(int nuevoContador) {
    FILE *contadorArchivo = fopen("contador.txt", "w");
    if (contadorArchivo == NULL) {
        printf("Error al abrir el archivo del contador.\n");
        return;
    }
    fprintf(contadorArchivo, "%d", nuevoContador);
    fclose(contadorArchivo);
}


void Ingresar() {
    FILE *archivo = fopen("archivo.dat", "a");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }
    
    int numeroFila = ObtenerContador();

    numeroFila++;

    char marca[100], modelo[100], tipo_gasolina[100], color[100];
    float motor_cilindrada;
    int cantidad_asientos, cantidad_puertas;
    
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

    fprintf(archivo, "%d: %s-%s-%.1f-%s-%d-%d-%s\n", numeroFila, marca, modelo, motor_cilindrada, tipo_gasolina, cantidad_asientos, cantidad_puertas, color);
    printf("Auto ingresado con exito.\n");

    ActualizarContador(numeroFila);

    fclose(archivo);
}


void Mostrar() {
    FILE *archivo = fopen("archivo.dat", "r");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    char linea[1000];
    while (fgets(linea, sizeof(linea), archivo) != NULL) {
        printf("%s \n", linea);
    }

    fclose(archivo);
}

<<<<<<< HEAD
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

void Modificar() {
    FILE *archivoLectura = fopen("archivo.dat", "r");
    if (archivoLectura == NULL) {
        printf("No se pudo abrir el archivo para lectura.\n");
        return;
    }

    FILE *archivoTemporal = fopen("temporal.dat", "w");
    if (archivoTemporal == NULL) {
        printf("No se pudo abrir el archivo temporal.\n");
        fclose(archivoLectura);
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
=======
>>>>>>> e2ee8b2170e2d340c7a5c59ba3748d32e6d1a15c


void CambiarFormatoEnArchivo() {
    FILE *archivo = fopen("archivo.dat", "r+");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    char formato;
    printf("Ingresa el nuevo separador ('-' o '/' o ';' o ':'): ");
    scanf(" %c", &formato);

    int caracter;
    while ((caracter = fgetc(archivo)) != EOF) {
        if (caracter == '-' || caracter == '/' || caracter == ';' || caracter == ':') {
            fseek(archivo, -1, SEEK_CUR);
            fputc(formato, archivo);
            fseek(archivo, 0, SEEK_CUR);
        }
    }

    fclose(archivo);
    printf("Cambio de separador realizado correctamente.\n");
}

void Eliminar() {
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

int main() {
    int opcion;
    do {
        printf("-------------------- CRUD DE AUTOMOVILES --------------------");
        printf("\nMenu de opciones:\n");
<<<<<<< HEAD
        printf("1. Ingresar\n");
        printf("2. Mostrar\n");
        printf("3. Eliminar\n");
        printf("4. Modificar \n");
        printf("5. Cambiar el formato en el archivo.dat\n");
        printf("0. Salir\n");
=======
        printf("1.- Ingresar\n");
        printf("2.- Mostrar\n");
        printf("3.- Eliminar\n");
        printf("4.- Cambiar el separador\n");
        printf("5.- Modificar (No disponible)\n");
        printf("0.- Salir\n");
>>>>>>> e2ee8b2170e2d340c7a5c59ba3748d32e6d1a15c
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
