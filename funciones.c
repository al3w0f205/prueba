#include <stdio.h>
#include <string.h>
#include "funciones.h"


int menu(){
    int opc = 0;
    printf("\n===== SISTEMA DE OPTIMIZACION DE PRODUCCION =====\n");
    printf("1. Registrar producto\n");
    printf("2. Ver productos\n");
    printf("3. Buscar producto\n");
    printf("4. Editar producto\n");
    printf("5. Eliminar producto\n");
    printf("6. Calcular tiempo y recursos totales\n");
    printf("7. Verificar factibilidad de produccion\n");
    printf("8. Salir\n");
    printf(">> ");
    opc = validarEnteroConRango(1, 8);
    return opc;
}

void registrarProducto(char nombres[][TAM], float *tiempos, float *recursos, int *cantidades, int *cont){
    if (*cont >= MAX){
        printf("No se pueden registrar mas productos (maximo %d)\n", MAX);
        return;
    }
    printf("Ingrese el nombre del producto %d: ", *cont + 1);
    leerCadena(nombres[*cont], TAM);
    for (int i = 0; i < *cont; i++){
        if (strcmp(nombres[i], nombres[*cont]) == 0){
            printf("Ya existe un producto con ese nombre\n");
            nombres[*cont][0] = '\0';
            return;
        }
    }
    printf("Ingrese la cantidad demandada del producto %d: ", *cont + 1);
    cantidades[*cont] = validarEnteroConRango(1, 100000);
    printf("Ingrese el tiempo de fabricacion por unidad (horas) del producto %d: ", *cont + 1);
    tiempos[*cont] = validarFloatConRango(0.01, 100000);
    printf("Ingrese los recursos por unidad del producto %d: ", *cont + 1);
    recursos[*cont] = validarFloatConRango(0.01, 100000);
    (*cont)++;
    printf("Producto registrado exitosamente (%d/%d)\n", *cont, MAX);
}

void verProductos(char nombres[][TAM], float *tiempos, float *recursos, int *cantidades, int *cont){
    if (*cont == 0){
        printf("No hay productos registrados\n");
        return;
    }
    float tiempoProducto = 0;
    float recursosProducto = 0;
    printf("\nProductos registrados:\n\n");
    printf("#\tNombre\t\t\tCantidad\tTiempo(h/u)\tRecursos/u\tTiempo Total\tRecursos Total\n");
    printf("---\t------\t\t\t--------\t-----------\t----------\t------------\t--------------\n");
    for (int i = 0; i < *cont; i++){
        tiempoProducto = tiempos[i] * cantidades[i];
        recursosProducto = recursos[i] * cantidades[i];
        printf("%d\t%-20s\t%d\t\t%.2f\t\t%.2f\t\t%.2f\t\t%.2f\n",
                i + 1,
                nombres[i],
                cantidades[i],
                tiempos[i],
                recursos[i],
                tiempoProducto,
                recursosProducto);
    }
    printf("\nTotal de productos: %d/%d\n", *cont, MAX);
}

int buscarIndice(char nombres[][TAM], int *cont, char *nombre){
    for (int i = 0; i < *cont; i++){
        if (strcmp(nombres[i], nombre) == 0){
            return i;
        }
    }
    return -1;
}

void buscarProducto(char nombres[][TAM], float *tiempos, float *recursos, int *cantidades, int *cont){
    char nombreBuscar[TAM];
    int indice = 0;
    int f = 0;
    if (*cont == 0){
        printf("No hay productos registrados\n");
        return;
    }
    printf("Ingrese el nombre del producto que desea buscar: ");
    leerCadena(nombreBuscar, TAM);
    for (int i = 0; i < *cont; i++){
        if (strcmp(nombres[i], nombreBuscar) == 0){
            indice = i;
            f = 1;
            break;
        }
    }
    if (f == 0){
        printf("No se encontro el producto\n");
    } else {
        printf("Producto encontrado:\n");
        printf("Nombre: %s\n", nombres[indice]);
        printf("Cantidad demandada: %d\n", cantidades[indice]);
        printf("Tiempo de fabricacion: %.2f horas/unidad\n", tiempos[indice]);
        printf("Recursos por unidad: %.2f\n", recursos[indice]);
        printf("Tiempo total: %.2f horas\n", tiempos[indice] * cantidades[indice]);
        printf("Recursos totales: %.2f\n", recursos[indice] * cantidades[indice]);
    }
}

void editarProducto(char nombres[][TAM], float *tiempos, float *recursos, int *cantidades, int *cont){
    char nombreBuscar[TAM];
    int indice;
    int opcion;
    if (*cont == 0){
        printf("No hay productos registrados\n");
        return;
    }
    printf("Ingrese el nombre del producto a editar: ");
    leerCadena(nombreBuscar, TAM);
    indice = buscarIndice(nombres, cont, nombreBuscar);
    if (indice == -1){
        printf("No se encontro el producto\n");
        return;
    }
    printf("\nProducto encontrado:\n");
    printf("Nombre: %s\n", nombres[indice]);
    printf("Cantidad: %d\n", cantidades[indice]);
    printf("Tiempo: %.2f horas/unidad\n", tiempos[indice]);
    printf("Recursos: %.2f unidades/unidad\n", recursos[indice]);
    printf("\nQue desea editar?\n");
    printf("1. Nombre\n");
    printf("2. Cantidad demandada\n");
    printf("3. Tiempo de fabricacion\n");
    printf("4. Recursos por unidad\n");
    printf("5. Todos los campos\n");
    printf(">> ");
    opcion = validarEnteroConRango(1, 5);
    switch (opcion){
        case 1:
            printf("Nuevo nombre: ");
            leerCadena(nombres[indice], TAM);
            break;
        case 2:
            printf("Nueva cantidad demandada: ");
            cantidades[indice] = validarEnteroConRango(1, 100000);
            break;
        case 3:
            printf("Nuevo tiempo de fabricacion (horas/unidad): ");
            tiempos[indice] = validarFloatConRango(0.01, 100000);
            break;
        case 4:
            printf("Nuevos recursos por unidad: ");
            recursos[indice] = validarFloatConRango(0.01, 100000);
            break;
        case 5:
            printf("Nuevo nombre: ");
            leerCadena(nombres[indice], TAM);
            printf("Nueva cantidad demandada: ");
            cantidades[indice] = validarEnteroConRango(1, 100000);
            printf("Nuevo tiempo de fabricacion (horas/unidad): ");
            tiempos[indice] = validarFloatConRango(0.01, 100000);
            printf("Nuevos recursos por unidad: ");
            recursos[indice] = validarFloatConRango(0.01, 100000);
            break;
    }
    printf("Producto actualizado exitosamente\n");
}

void eliminarProducto(char nombres[][TAM], float *tiempos, float *recursos, int *cantidades, int *cont){
    char nombreBuscar[TAM];
    int indice;
    char confirmacion;
    if (*cont == 0){
        printf("No hay productos registrados\n");
        return;
    }
    printf("Ingrese el nombre del producto a eliminar: ");
    leerCadena(nombreBuscar, TAM);
    indice = buscarIndice(nombres, cont, nombreBuscar);
    if (indice == -1){
        printf("No se encontro el producto\n");
        return;
    }
    printf("Producto encontrado: %s\n", nombres[indice]);
    printf("Confirmar eliminacion? (s/n): ");
    scanf("%c", &confirmacion);
    while ((getchar()) != '\n');
    if (confirmacion == 's' || confirmacion == 'S'){
        for (int i = indice; i < *cont - 1; i++){
            strcpy(nombres[i], nombres[i + 1]);
            cantidades[i] = cantidades[i + 1];
            tiempos[i] = tiempos[i + 1];
            recursos[i] = recursos[i + 1];
        }
        (*cont)--;
        printf("Producto eliminado exitosamente (%d/%d)\n", *cont, MAX);
    } else {
        printf("Eliminacion cancelada\n");
    }
}

void calcularTotales(float *tiempos, float *recursos, int *cantidades, int *cont, float *tiempoTotal, float *recursosTotal){
    *tiempoTotal = 0;
    *recursosTotal = 0;
    for (int i = 0; i < *cont; i++){
        *tiempoTotal += tiempos[i] * cantidades[i];
        *recursosTotal += recursos[i] * cantidades[i];
    }
}

void verificarFactibilidad(float *tiempos, float *recursos, int *cantidades, int *cont){
    float tiempoTotal = 0;
    float recursosTotal = 0;
    float tiempoDisponible = 0;
    float recursosDisponibles = 0;
    if (*cont == 0){
        printf("No hay productos registrados\n");
        return;
    }
    calcularTotales(tiempos, recursos, cantidades, cont, &tiempoTotal, &recursosTotal);
    printf("Ingrese el tiempo total disponible (horas): ");
    tiempoDisponible = validarFloatConRango(0.01, 1000000);
    printf("Ingrese los recursos totales disponibles: ");
    recursosDisponibles = validarFloatConRango(0.01, 1000000);
    printf("\n===== RESULTADO DE FACTIBILIDAD =====\n");
    printf("Tiempo requerido:     %.2f horas\n", tiempoTotal);
    printf("Tiempo disponible:    %.2f horas\n", tiempoDisponible);
    printf("Recursos requeridos:  %.2f unidades\n", recursosTotal);
    printf("Recursos disponibles: %.2f unidades\n", recursosDisponibles);
    printf("=====================================\n");
    if (tiempoTotal <= tiempoDisponible && recursosTotal <= recursosDisponibles){
        printf("La produccion ES FACTIBLE\n");
        printf("Tiempo sobrante: %.2f horas\n", tiempoDisponible - tiempoTotal);
        printf("Recursos sobrantes: %.2f unidades\n", recursosDisponibles - recursosTotal);
    } else {
        printf("La produccion NO ES FACTIBLE\n");
        if (tiempoTotal > tiempoDisponible){
            printf("Deficit de tiempo: %.2f horas adicionales necesarias\n", tiempoTotal - tiempoDisponible);
        }
        if (recursosTotal > recursosDisponibles){
            printf("Deficit de recursos: %.2f unidades adicionales necesarias\n", recursosTotal - recursosDisponibles);
        }
    }
}

void leerCadena(char *cadena, int n){
    int len;
    fgets(cadena, n, stdin);
    len = strlen(cadena) - 1;
    cadena[len] = '\0';
}

int validarEnteroConRango(int a, int b){
    int aux;
    int n;
    do {
        aux = scanf("%d", &n);
        while ((getchar()) != '\n');
        if (aux != 1 || n < a || n > b){
            printf("Error: el valor ingresado es incorrecto: ");
            printf(">> ");
        }
    } while (aux != 1 || n < a || n > b);
    return n;
}

float validarFloatConRango(float a, float b){
    int aux;
    float n;
    do {
        aux = scanf("%f", &n);
        while ((getchar()) != '\n');
        if (aux != 1 || n < a || n > b){
            printf("Error: el valor ingresado es incorrecto: ");
            printf(">> ");
        }
    } while (aux != 1 || n < a || n > b);
    return n;
}
