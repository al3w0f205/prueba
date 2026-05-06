#include <stdio.h>
#include <string.h>
#include "funciones.h"

int menu()
{
    int opc = 0;
    printf("\n------------------------------------\n");
    printf("SISTEMA DE OPTIMIZACION DE PRODUCCION\n");
    printf("------------------------------------\n\n");
    printf("1.Registrar producto\n");
    printf("2.Ver productos\n");
    printf("3.Buscar producto\n");
    printf("4.Editar producto\n");
    printf("5.Eliminar producto\n");
    printf("6.Calcular tiempo y materiales totales\n");
    printf("7.Verificar factibilidad de produccion\n");
    printf("8.Salir\n\n");
    printf("------------------------------------\n");
    printf(">> ");
    opc = validarEnteroConRango(1, 8);
    return opc;
}

void pedirNombre(char *destino, char *mensaje)
{
    printf("%s", mensaje);
    leerCadena(destino, 50);
    while (strlen(destino) == 0)
    {
        printf("\nError: el nombre no puede estar vacio\n");
        printf("%s", mensaje);
        leerCadena(destino, 50);
    }
}

float leerTiempo()
{
    int horas, minutos;
    printf("\nTiempo de fabricacion por unidad (horas y minutos):\n");
    printf("  Horas: ");
    horas = validarEnteroConRango(0, 1000);
    printf("  Minutos (0-59): ");
    minutos = validarEnteroConRango(0, 59);
    return horas + minutos / 60.0;
}

void imprimirDatosProducto(float *tiempos, float *recursos, int *cantidades, int indice, int conTotales)
{
    int horasEnteras = (int)tiempos[indice];
    int minutosEnteros = (int)((tiempos[indice] - horasEnteras) * 60);
    printf("  Unidades a fabricar: %d\n", cantidades[indice]);
    printf("  Tiempo por unidad: %dh %dmin\n", horasEnteras, minutosEnteros);
    printf("  Materiales por unidad: %.2f\n", recursos[indice]);
    if (conTotales == 1)
    {
        printf("  Tiempo total: %.2f horas\n", tiempos[indice] * cantidades[indice]);
        printf("  Materiales totales: %.2f\n", recursos[indice] * cantidades[indice]);
    }
}

void registrarProducto(char nombres[][50], float *tiempos, float *recursos, int *cantidades, int *cont)
{
    if (*cont >= 5)
    {
        printf("\nNo se pueden registrar mas productos (maximo 5)\n");
        return;
    }
    printf("\n------------------------------------\n");
    printf("REGISTRO DE PRODUCTO %d\n", *cont + 1);
    printf("------------------------------------\n\n");

    pedirNombre(nombres[*cont], "Nombre del producto: ");
    if (buscarIndice(nombres, cont, nombres[*cont]) != -1)
    {
        printf("\nYa existe un producto con ese nombre\n");
        nombres[*cont][0] = '\0';
        return;
    }

    printf("\nCantidad de unidades a fabricar: ");
    cantidades[*cont] = validarEnteroConRango(1, 100000);

    tiempos[*cont] = leerTiempo();

    printf("\nMateriales necesarios por unidad (cantidad): ");
    recursos[*cont] = validarFloatConRango(0, 100000);
    (*cont)++;

    printf("\n------------------------------------\n");
    printf("Producto registrado exitosamente (%d/5)\n", *cont);
    printf("------------------------------------\n");
}

void verProductos(char nombres[][50], float *tiempos, float *recursos, int *cantidades, int *cont)
{
    if (*cont == 0)
    {
        printf("\nNo hay productos registrados\n");
        return;
    }
    printf("\n------------------------------------\n");
    printf("LISTA DE PRODUCTOS\n");
    printf("------------------------------------\n");
    for (int i = 0; i < *cont; i++)
    {
        printf("\nProducto %d: %s\n", i + 1, nombres[i]);
        imprimirDatosProducto(tiempos, recursos, cantidades, i, 1);
    }
    printf("\n------------------------------------\n");
    printf("Total de productos: %d/5\n", *cont);
    printf("------------------------------------\n");
}

int buscarIndice(char nombres[][50], int *cont, char *nombre)
{
    for (int i = 0; i < *cont; i++)
    {
        if (strcmp(nombres[i], nombre) == 0)
        {
            return i;
        }
    }
    return -1;
}

void buscarProducto(char nombres[][50], float *tiempos, float *recursos, int *cantidades, int *cont)
{
    char nombreBuscar[50];
    int indice = 0;
    if (*cont == 0)
    {
        printf("\nNo hay productos registrados\n");
        return;
    }
    printf("\nIngrese el nombre del producto que desea buscar: ");
    leerCadena(nombreBuscar, 50);
    indice = buscarIndice(nombres, cont, nombreBuscar);
    if (indice == -1)
    {
        printf("\nNo se encontro el producto\n");
        return;
    }
    
    printf("\n------------------------------------\n");
    printf("Producto encontrado:\n\n");
    printf("  Nombre: %s\n", nombres[indice]);
    imprimirDatosProducto(tiempos, recursos, cantidades, indice, 1);
    printf("\n------------------------------------\n");
}

void editarProducto(char nombres[][50], float *tiempos, float *recursos, int *cantidades, int *cont)
{
    char nombreBuscar[50];
    int indice;
    int opcion;
    if (*cont == 0)
    {
        printf("\nNo hay productos registrados\n");
        return;
    }
    printf("\nIngrese el nombre del producto a editar: ");
    leerCadena(nombreBuscar, 50);
    indice = buscarIndice(nombres, cont, nombreBuscar);
    if (indice == -1)
    {
        printf("\nNo se encontro el producto\n");
        return;
    }
    printf("\n------------------------------------\n");
    printf("Producto encontrado:\n\n");
    printf("  Nombre: %s\n", nombres[indice]);
    imprimirDatosProducto(tiempos, recursos, cantidades, indice, 0);
    printf("\n------------------------------------\n");

    printf("\nQue desea editar?\n\n");
    printf("1.Nombre\n");
    printf("2.Unidades a fabricar\n");
    printf("3.Tiempo de fabricacion\n");
    printf("4.Materiales por unidad\n");
    printf("5.Todos los campos\n\n");
    printf(">> ");
    opcion = validarEnteroConRango(1, 5);
    switch (opcion)
    {
    case 1:
        pedirNombre(nombres[indice], "\nNuevo nombre: ");
        break;
    case 2:
        printf("\nNueva cantidad de unidades a fabricar: ");
        cantidades[indice] = validarEnteroConRango(1, 100000);
        break;
    case 3:
        tiempos[indice] = leerTiempo();
        break;
    case 4:
        printf("\nNuevos materiales por unidad: ");
        recursos[indice] = validarFloatConRango(0, 100000);
        break;
    case 5:
        pedirNombre(nombres[indice], "\nNuevo nombre: ");
        printf("\nNueva cantidad de unidades a fabricar: ");
        cantidades[indice] = validarEnteroConRango(1, 100000);
        tiempos[indice] = leerTiempo();
        printf("\nNuevos materiales por unidad: ");
        recursos[indice] = validarFloatConRango(0, 100000);
        break;
    }
    printf("\n------------------------------------\n");
    printf("Producto actualizado exitosamente\n");
    printf("------------------------------------\n");
}

void eliminarProducto(char nombres[][50], float *tiempos, float *recursos, int *cantidades, int *cont)
{
    char nombreBuscar[50];
    int indice;
    int confirmacion;
    if (*cont == 0)
    {
        printf("\nNo hay productos registrados\n");
        return;
    }
    printf("\nIngrese el nombre del producto a eliminar: ");
    leerCadena(nombreBuscar, 50);
    indice = buscarIndice(nombres, cont, nombreBuscar);
    if (indice == -1)
    {
        printf("\nNo se encontro el producto\n");
        return;
    }
    printf("\nProducto encontrado: %s\n", nombres[indice]);
    printf("\nConfirmar eliminacion 1.Si/2.No: ");
    confirmacion = validarEnteroConRango(1, 2);
    if (confirmacion == 1)
    {
        for (int i = indice; i < *cont - 1; i++)
        {
            strcpy(nombres[i], nombres[i + 1]);
            cantidades[i] = cantidades[i + 1];
            tiempos[i] = tiempos[i + 1];
            recursos[i] = recursos[i + 1];
        }
        (*cont)--;
        printf("\nProducto eliminado exitosamente (%d/5)\n", *cont);
    }
    else
    {
        printf("\nEliminacion cancelada\n");
    }
}

void calcularTotales(float *tiempos, float *recursos, int *cantidades, int *cont, float *tiempoTotal, float *recursosTotal)
{
    *tiempoTotal = 0;
    *recursosTotal = 0;
    for (int i = 0; i < *cont; i++)
    {
        *tiempoTotal += tiempos[i] * cantidades[i];
        *recursosTotal += recursos[i] * cantidades[i];
    }
}

void verificarFactibilidad(float *tiempos, float *recursos, int *cantidades, int *cont)
{
    float tiempoTotal = 0;
    float recursosTotal = 0;
    float tiempoDisponible = 0;
    float recursosDisponibles = 0;
    float porcentajeTiempo = 0;
    float porcentajeMateriales = 0;
    int factible = 1;
    if (*cont == 0)
    {
        printf("\nNo hay productos registrados\n");
        return;
    }
    
    calcularTotales(tiempos, recursos, cantidades, cont, &tiempoTotal, &recursosTotal);
    
    printf("\n------------------------------------\n");
    printf("VERIFICAR FACTIBILIDAD\n");
    printf("------------------------------------\n");

    printf("\nIngrese el tiempo total disponible en la fabrica (horas): ");
    tiempoDisponible = validarFloatConRango(0.01, 1000000);

    printf("\nIngrese los materiales totales disponibles: ");
    recursosDisponibles = validarFloatConRango(0.01, 1000000);

    printf("\n------------------------------------\n");
    printf("RESULTADO\n");
    printf("------------------------------------\n\n");
    printf("Tiempo requerido: %.2f horas\n", tiempoTotal);
    printf("Tiempo disponible: %.2f horas\n\n", tiempoDisponible);
    printf("Materiales requeridos: %.2f unidades\n", recursosTotal);
    printf("Materiales disponibles: %.2f unidades\n", recursosDisponibles);
    porcentajeTiempo = (tiempoTotal / tiempoDisponible) * 100;
    porcentajeMateriales = (recursosTotal / recursosDisponibles) * 100;
    printf("Uso de tiempo: %.1f%%\n", porcentajeTiempo);
    printf("Uso de materiales: %.1f%%\n", porcentajeMateriales);
    printf("\n------------------------------------\n");
    if (tiempoTotal > tiempoDisponible)
    {
        factible = 0;
    }
    if (recursosTotal > recursosDisponibles)
    {
        factible = 0;
    }
    if (factible == 1)
    {
        printf("\nLa produccion ES FACTIBLE\n\n");
        printf("Tiempo sobrante: %.2f horas\n", tiempoDisponible - tiempoTotal);
        printf("Materiales sobrantes: %.2f unidades\n", recursosDisponibles - recursosTotal);
    }
    else
    {
        printf("\nLa produccion NO ES FACTIBLE\n\n");
        if (tiempoTotal > tiempoDisponible)
        {
            printf("Faltan %.2f horas para completar la produccion\n", tiempoTotal - tiempoDisponible);
        }
        if (recursosTotal > recursosDisponibles)
        {
            printf("Faltan %.2f unidades de materiales\n", recursosTotal - recursosDisponibles);
        }
    }
}

void leerCadena(char *cadena, int n)
{
    int len;
    fgets(cadena, n, stdin);
    len = strlen(cadena) - 1;
    cadena[len] = '\0';
}

int validarEnteroConRango(int a, int b)
{
    int aux;
    int n;
    do
    {
        aux = scanf("%d", &n);
        while ((getchar()) != '\n')
            ;
        if (aux != 1 || n < a || n > b)
        {
            printf("Error: ingrese un numero entero entre %d y %d\n", a, b);
            printf(">> ");
        }
    } while (aux != 1 || n < a || n > b);
    return n;
}

float validarFloatConRango(float a, float b)
{
    int aux;
    float n;
    do
    {
        aux = scanf("%f", &n);
        while ((getchar()) != '\n')
            ;
        if (aux != 1 || n < a || n > b)
        {
            printf("Error: ingrese un numero entre %.2f y %.2f\n", a, b);
            printf(">> ");
        }
    } while (aux != 1 || n < a || n > b);
    return n;
}
