#include <stdio.h>
#include "funciones.h"


int main(){
    char nombres[MAX][TAM];
    int cantidades[MAX];
    float tiempos[MAX];
    float recursos[MAX];
    int cont = 0;
    int opc;

    do {
        opc = menu();
        switch (opc){
            case 1:
                registrarProducto(nombres, tiempos, recursos, cantidades, &cont);
                break;
            case 2:
                verProductos(nombres, tiempos, recursos, cantidades, &cont);
                break;
            case 3:
                buscarProducto(nombres, tiempos, recursos, cantidades, &cont);
                break;
            case 4:
                editarProducto(nombres, tiempos, recursos, cantidades, &cont);
                break;
            case 5:
                eliminarProducto(nombres, tiempos, recursos, cantidades, &cont);
                break;
            case 6:{
                float tiempoTotal = 0;
                float recursosTotal = 0;
                if (cont == 0){
                    printf("No hay productos registrados\n");
                    break;
                }
                calcularTotales(tiempos, recursos, cantidades, &cont, &tiempoTotal, &recursosTotal);
                printf("\nResumen de produccion:\n");
                printf("Tiempo total requerido: %.2f horas\n", tiempoTotal);
                printf("Recursos totales necesarios: %.2f unidades\n", recursosTotal);
                break;
            }
            case 7:
                verificarFactibilidad(tiempos, recursos, cantidades, &cont);
                break;
            case 8:
                printf("Saliendo del sistema...\n");
                break;
        }
    } while (opc != 8);

    return 0;
}
