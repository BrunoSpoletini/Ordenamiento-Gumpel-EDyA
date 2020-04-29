#include "funcgenerarpersonas.h"

int main (int argc, char *argv[]) {
    srand (time(NULL));
    int cantDatos;

    printf("Ingrese el numero de datos a generar:\n");
    scanf("%d", &cantDatos);

    generar_personas("nombres1.txt", "paises.txt", "output.txt", cantDatos);
    
    return 0;
}