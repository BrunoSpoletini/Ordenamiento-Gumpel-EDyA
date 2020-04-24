#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "persona.h"

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

char **leer_paises (char *archivoPaises, int *numPaises){
    int i;
    FILE* puntPaises = fopen(archivoPaises, "r");

    (*numPaises) = contar_lineas(puntPaises);
    char pais[TAM_LINEA];
    char **arrayPaises = malloc(sizeof(char*) * (*numPaises));
    
    for(i=0; (fscanf(puntPaises, "%[^\n]\n", pais) != EOF); i++){
        arrayPaises[i] = malloc(sizeof(pais));
        strcpy(arrayPaises[i], pais);
    }
    fclose(puntPaises);
    return arrayPaises;
}

int *genera_lista_random(int cantDatos, int numPaises){
    int i;
    int *arrayRandoms;
    arrayRandoms = malloc(sizeof(int) * cantDatos);
    for(i = 0; i < cantDatos; i++){
        arrayRandoms[i] = rand() % (numPaises+1);
    }
    printf("Paso el qsort");
    qsort(arrayRandoms, cantDatos, sizeof(int), greater_equal);
    printf("Paso el qsort");
    return arrayRandoms;
}

void generar_personas (int numPaises, char **arrayPaises, char *archivoPersonas, char *archivoSalida, int cantDatos){
    int cantLeidos=0, edad, *arrayRandoms, i;
    char nombre[TAM_LINEA], lugarDeNacimiento[TAM_LINEA];
    
    arrayRandoms = genera_lista_random(cantDatos, numPaises);

    for(i=0;i<cantDatos;i++){
        printf("%d\n", arrayRandoms[i]);
    }
    printf("hgola");

    FILE *puntPersonas = fopen(archivoPersonas, "r");

    FILE *puntSalida = fopen(archivoSalida, "w+");

    for(i=0; cantLeidos < cantDatos; i++){
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
    free(arrayRandoms);
}

int main(int argc, char *argv[]){
    srand (time(NULL));
    int cantDatos, numPaises;
    char **arrayPaises;

    printf("Ingrese el numero de datos a generar:\n");
    scanf("%d", &cantDatos);
    printf("#\n");
    arrayPaises = leer_paises("paises.txt", &numPaises);
    generar_personas(numPaises, arrayPaises, "nombres1.txt", "output.txt", cantDatos);
    
    printf("#\n");
    return 0;
}