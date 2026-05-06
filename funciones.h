int menu();
void leerCadena(char *cadena, int n);
int validarEnteroConRango(int a, int b);
float validarFloatConRango(float a, float b);
void registrarProducto(char nombres[][50], float *tiempos, float *recursos, int *cantidades, int *cont);
void verProductos(char nombres[][50], float *tiempos, float *recursos, int *cantidades, int *cont);
int buscarIndice(char nombres[][50], int *cont, char *nombre);
void buscarProducto(char nombres[][50], float *tiempos, float *recursos, int *cantidades, int *cont);
void editarProducto(char nombres[][50], float *tiempos, float *recursos, int *cantidades, int *cont);
void eliminarProducto(char nombres[][50], float *tiempos, float *recursos, int *cantidades, int *cont);
void calcularTotales(float *tiempos, float *recursos, int *cantidades, int *cont, float *tiempoTotal, float *recursosTotal);
void verificarFactibilidad(float *tiempos, float *recursos, int *cantidades, int *cont);

