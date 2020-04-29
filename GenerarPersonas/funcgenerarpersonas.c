#include "funcgenerarpersonas.h"

int contar_lineas (FILE* fp) {
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

int greater_equal(const void *a, const void *b) {
   return ( *(int*)a - *(int*)b );
}

int *genera_lista_random (FILE* puntPersonas, int cantDatos) {
    int* arrayRandoms = malloc(sizeof(int) * cantDatos);
    int cantPersonas = contar_lineas(puntPersonas);

    for (int i = 0; i < cantDatos; ++i) {
        arrayRandoms[i] = (rand() % cantPersonas);
    }

    qsort(arrayRandoms, cantDatos, sizeof(int), greater_equal);

    return arrayRandoms;
}

char **leer_paises (char *archivoPaises, int *numPaises) {
    char pais[TAM_LINEA];
    FILE* puntPaises = fopen(archivoPaises, "r");

    (*numPaises) = contar_lineas(puntPaises);
    char **arrayPaises = malloc(sizeof(char*) * (*numPaises));
    
    for (int i = 0; (fscanf(puntPaises, "%[^\n]\n", pais) != EOF); ++i) {
        arrayPaises[i] = malloc(sizeof(pais));
        strcpy(arrayPaises[i], pais);
    }

    fclose(puntPaises);
    return arrayPaises;
}

void generar_personas (char* archivoPersonas, char* archivoPaises, char* archivoSalida, int cantDatos) {
    int numPaises;
    char** arrayPaises = leer_paises(archivoPaises, &numPaises);

    FILE* puntPersonas = fopen(archivoPersonas, "r");
    int cantLeidos = 0, edad;
    char nombre[TAM_LINEA], lugarDeNacimiento[TAM_LINEA];
    
    int *arrayRandoms = genera_lista_random(puntPersonas, cantDatos);

    FILE *puntSalida = fopen(archivoSalida, "w+");

    for (int linea = 0; cantLeidos < cantDatos; ++linea) {
        fscanf(puntPersonas,"%[^\n]\n", nombre);
        if (linea == arrayRandoms[cantLeidos]) {
            do{
                edad = (rand() % 100) + 1;
                strcpy(lugarDeNacimiento, arrayPaises[rand() % numPaises]);
                fprintf(puntSalida, "%s, %d, %s\n", nombre, edad, lugarDeNacimiento);
                cantLeidos++;
            } while (arrayRandoms[cantLeidos - 1] == arrayRandoms[cantLeidos]);
        }
    }

    fclose(puntPersonas);
    fclose(puntSalida);

    for (int i = 0; i < numPaises; ++i) {
        free(arrayPaises[i]);
    }
    free(arrayPaises);
    free(arrayRandoms);

}