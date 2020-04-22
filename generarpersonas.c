#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "persona.h"

#define TAM_LINEA 200

// Dado un puntero a un archivo, devuelve la cantidad de lineas escritas.
// contar_lineas: FILE* -> int.
int contar_lineas(FILE* fp) {
    int cantLineas = 0;
    if (fp != NULL) { // Si se puede abrir el archivo.
        char buffer[TAM_LINEA]; // Buffers

        while (fgets(buffer, TAM_LINEA, fp) != NULL) {
            cantLineas++;
        }
    } else {
        printf("No se pudo abrir el archivo que se quizo contar sus lineas.\n");
    }
    rewind(fp);
    return cantLineas;
}

// greater_equal es una función de comparación entre dos enteros, 
// que retorna un entero mayor o igual a 0 si a<=b, o un entero negativo si a > b.
int greater_equal(const void *a, const void *b) {
   return ( *(int*)a - *(int*)b );
}

int* genera_lista_random(FILE* fp, int cantDatos) {
    int i, random;

    int cantLineas = contar_lineas(fp);

    int *arrayContinuo = malloc(sizeof(int) * cantLineas);
    int *arrayRandoms = malloc(sizeof(int) * cantDatos);

    for (i=0; i<cantLineas; i++) {
        arrayContinuo[i]=i;
    }

    for(i=0; i < cantDatos; i++){
        random = rand() % (cantLineas-i-1);
        arrayRandoms[i]=arrayContinuo[random];
        arrayContinuo[random]=arrayContinuo[cantLineas-i-1];
    }
    
    free (arrayContinuo);

    qsort(arrayRandoms, cantDatos, sizeof(int), greater_equal);

    return arrayRandoms;
}

void generar_personas (char* archivoPersonas, char* archivoPaises, char* archivoSalida, int cantDatos){
    char pais[TAM_LINEA];

    FILE* puntPaises = fopen(archivoPaises, "r");
    int numPaises = contar_lineas(puntPaises);

    char **arrayPaises = malloc(sizeof(char*) * numPaises);
    
    for(int i=0; (fscanf(puntPaises, "%[^\n]\n", pais) != EOF); i++){
    
        arrayPaises[i] = malloc(sizeof(pais));
        strcpy(arrayPaises[i], pais);
    }

    fclose(puntPaises);

    FILE* puntPersonas = fopen(archivoPersonas, "r");
    int cantLeidos=0, edad;
    char nombre[TAM_LINEA], lugarDeNacimiento[TAM_LINEA];
    
    int *arrayRandoms = genera_lista_random(puntPersonas, cantDatos);

    FILE *puntSalida = fopen(archivoSalida, "w+");

    for(int i=0; cantLeidos < cantDatos; i++){
        fscanf(puntPersonas,"%[^\n]\n", nombre);
        if(i == arrayRandoms[cantLeidos]){
            edad = (rand() % 100) + 1;
            strcpy(lugarDeNacimiento, arrayPaises[rand() % numPaises]);
            fprintf(puntSalida, "%s, %d, %s\n", nombre, edad, lugarDeNacimiento);
            cantLeidos++;
        }
    }

    fclose(puntPersonas);
    fclose(puntSalida);

    for(int i=0; i < numPaises; i++){
        free(arrayPaises[i]);
    }
    free(arrayPaises);

    free(arrayRandoms);

}

int main(int argc, char *argv[]){
    srand (time(NULL));
    int cantDatos;

    printf("Ingrese el numero de datos a generar:\n");
    scanf("%d", &cantDatos);

    generar_personas("nombres1.txt", "paises.txt", "output.txt", cantDatos);
    
    return 0;
}