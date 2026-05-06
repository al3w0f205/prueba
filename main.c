#include <stdio.h>
#include "funciones.h"

int main (int argc, char *argv[]) {

    char nombres[5][50];
    int cantidades[5];
    float tiempos[5];
    float recursos[5];
    int cont = 0;
    int opc = 0;

    do{
        opc = menu();

        switch (opc)
        {
        case 1:
            registrarProducto(nombres,tiempos,recursos,cantidades,&cont);
            break;
        case 2:
            verProductos(nombres,tiempos,recursos,cantidades,&cont);
            break;
        case 3:
            buscarProducto(nombres,tiempos,recursos,cantidades,&cont);
            break;
        case 4:
            editarProducto(nombres,tiempos,recursos,cantidades,&cont);
            break;
        case 5:
            eliminarProducto(nombres,tiempos,recursos,cantidades,&cont);
            break;
        case 6:{
            float tiempoTotal = 0;
            float recursosTotal = 0;
            if (cont == 0)
            {
                printf("No hay productos registrados\n");
                break;
            }
            calcularTotales(tiempos,recursos,cantidades,&cont,&tiempoTotal,&recursosTotal);
            printf("\n------------------------------------\n");
            printf("Resumen de produccion:\n");
            printf("Tiempo total requerido: %.2f horas\n",tiempoTotal);
            printf("Materiales totales necesarios: %.2f unidades\n",recursosTotal);
            printf("------------------------------------\n");
            break;
        }
        case 7:
            verificarFactibilidad(tiempos,recursos,cantidades,&cont);
            break;
        case 8:
            printf("Saliendo del sistema...\n");
            return 0;
        }
    }while (opc != 8);

    return 0;
}

