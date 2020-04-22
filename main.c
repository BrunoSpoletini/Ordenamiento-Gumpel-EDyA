#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "persona.h"

#define TAM_BUFFER 200

// Dado un puntero a un archivo, devuelve la cantidad de lineas escritas.
// contar_lineas: FILE* -> int.
int contar_lineas(FILE* fp) {
    int cantLineas = 0;
    if (fp != NULL) { // Si se puede abrir el archivo.
        char buffer[TAM_BUFFER]; // Buffers

        while (fgets(buffer, TAM_BUFFER, fp) != NULL) {
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


// Dados un puntero a un archivo y una cantidad de randoms que se necesitan, 
// devuelve un array con los numeros random que se necesitan menores que las lineas del archivo sin repetir
// genera_lista_random: FILE*, int -> int*
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


// Dados el nombre de un archivo de entrada y la cantidad de personas necesarias, 
// devuelve una lista de personas aleatorias, sin repetir.
// leer_archivo_personas: char*, int -> Persona*
Persona* leer_archivo_personas(char* nombreArchivo, int cantDatos) {
    FILE* fp = fopen(nombreArchivo, "r");
    int cantLeidos=0, i;
    char buffer[TAM_BUFFER];
    
    int *arrayRandoms = genera_lista_random(fp, cantDatos);

    Persona *listaPersonas = malloc(sizeof(Persona) * cantDatos);

    for(i=0; cantLeidos < cantDatos; i++){
        fscanf(fp,"%[^\n]\n", buffer);
        if(i == arrayRandoms[cantLeidos]){
            listaPersonas[cantLeidos].edad = (rand() % 100) + 1;
            listaPersonas[cantLeidos].nombre = malloc(sizeof(buffer));
            strcpy(listaPersonas[cantLeidos].nombre, buffer);
            cantLeidos++;
        }
    }
    fclose(fp);

    free(arrayRandoms);

    return listaPersonas;
}

// leer_archivo_paises recibe la cantidad de datos a generar, y una lista de estructuras
// de tipo Persona y rellena el campo de "lugarDeNacimiento" de la estructura
void leer_archivo_paises(char *nombreArchivo, int cantDatos, Persona *listaPersonas){
    int i, random;
    char buffer[TAM_BUFFER];

    FILE* fp = fopen(nombreArchivo, "r");
    int numLineas = contar_lineas(fp);

    char **arrayPaises = malloc(sizeof(char*) * numLineas);
    
    for(i=0; (fscanf(fp, "%[^\n]\n", buffer) != EOF); i++){
    
        arrayPaises[i] = malloc(sizeof(buffer));
        strcpy(arrayPaises[i], buffer);
    }

    for(i=0; i < cantDatos; i++){
        random = rand() % numLineas;
        listaPersonas[i].lugarDeNacimiento = malloc(sizeof(buffer));
        strcpy(listaPersonas[i].lugarDeNacimiento, arrayPaises[random]);
    }

    for(i=0; i < numLineas; i++){
        free(arrayPaises[i]);
    }
    free(arrayPaises);
}

// Dados una lista de personas y la cantidad de personas en esta,
// libera el espacio en memoria de la lista
void liberar_personas(Persona *listaPersonas, int cantDatos){
    int i;

    for(i=0; i < cantDatos; i++){
        free(listaPersonas[i].nombre);
        free(listaPersonas[i].lugarDeNacimiento);
    }

    free(listaPersonas);
}

// Dados el nombre del archivo de salida, una lista de personas y la cantidad de personas en esta,
// escribe en el archivo de salida las personas en la lista.
void write_output(char *nombreArchivo, Persona *listaPersonas, int cantDatos){ 
    int i=0;

    FILE *fp = fopen(nombreArchivo, "w+");

    for(i = 0; i < cantDatos; i++){
        fprintf(fp, "%s, %d, %s\n", listaPersonas[i].nombre, listaPersonas[i].edad, listaPersonas[i].lugarDeNacimiento);
    }

    fclose(fp);
}

int main(int argc, char *argv[]){
    srand (time(NULL));
    int cantDatos;

    printf("Ingrese el numero de datos a generar:\n");
    scanf("%d", &cantDatos);

    Persona *listaPersonas;

    listaPersonas = leer_archivo_personas("nombres1.txt", cantDatos);

    leer_archivo_paises("paises.txt", cantDatos, listaPersonas);

    write_output("output.txt",listaPersonas, cantDatos);

    liberar_personas(listaPersonas, cantDatos);
    
    return 0;
}