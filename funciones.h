#ifndef FUNCIONES_H
#define FUNCIONES_H

#define MAX 5
#define TAM 50

int menu();
void registrarProducto(char nombres[][TAM], float *tiempos, float *recursos, int *cantidades, int *cont);
void verProductos(char nombres[][TAM], float *tiempos, float *recursos, int *cantidades, int *cont);
int buscarIndice(char nombres[][TAM], int *cont, char *nombre);
void buscarProducto(char nombres[][TAM], float *tiempos, float *recursos, int *cantidades, int *cont);
void editarProducto(char nombres[][TAM], float *tiempos, float *recursos, int *cantidades, int *cont);
void eliminarProducto(char nombres[][TAM], float *tiempos, float *recursos, int *cantidades, int *cont);
void calcularTotales(float *tiempos, float *recursos, int *cantidades, int *cont, float *tiempoTotal, float *recursosTotal);
void verificarFactibilidad(float *tiempos, float *recursos, int *cantidades, int *cont);
void leerCadena(char *cadena, int n);
int validarEnteroConRango(int a, int b);
float validarFloatConRango(float a, float b);

#endif
