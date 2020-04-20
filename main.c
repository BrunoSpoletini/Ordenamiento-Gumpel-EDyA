#include <stdio.h>
#include <stdlib.h>
//#include <math.h>
#include <string.h>
#include <time.h>

typedef struct {
char * nombre ;
int edad ;
char * lugarDeNacimiento ; // pais o capital
} Persona ;


// Dado el nombre de un archivo, devuelve la cantidad de lineas escritas.
// contar_lineas: char[] -> int.
int contar_lineas(FILE* fp){
    int numero_lineas = 0;
    if(fp != NULL) { // Si se puede abrir el archivo.
        char buffer[1010]; // Buffers

        while(fgets(buffer, 1010 ,fp) != NULL){
            numero_lineas++;
        }
    }
    else
    {
        printf("No se pudo abrir el archivo que se quizo contar sus lineas.\n");
    }
    rewind(fp);
    return numero_lineas;
}


// greaterEqual es una función de comparación entre dos enteros, 
// que retorna un entero mayor o igual a 0 si a<=b, o un entero negativo si a > b.
int greater_equal(const void *a, const void *b){
   return ( *(int*)a - *(int*)b );
}

int *genera_lista_random(FILE *fp,int numDatos){
    int i, random;

    int numLineas = contar_lineas(fp);

    int *arrayContinuo = malloc(sizeof(int) * numLineas);
    int *arrayRandoms = malloc(sizeof(int) * numDatos);
    for(i=0;i<numLineas;i++){
        arrayContinuo[i]=i;
    }
    for(i = 0; i < numDatos; i++){
        random = rand() % (numLineas-i-1);
        arrayRandoms[i]=arrayContinuo[random];
        arrayContinuo[random]=arrayContinuo[numLineas-i-1];
    }
    
    free (arrayContinuo);
    qsort(arrayRandoms, numDatos, sizeof(int), greater_equal);
    return arrayRandoms;
}


// leerArchivos toma un puntero a un archivo, una lista de enteros (las líneas a leer del archivo), 
// la cantidad de líneas a leer y la cantidad de líneas que hay en el archivo a leer.
// Devuelve una lista de cadenas cuyos elementos son las líneas del archivo leído.
Persona *leer_archivo_personas(char nombreArchivo[], int numDatos){
    FILE* fp = fopen(nombreArchivo, "r");
    int cantLeidos=0, i;
    char buffer[1010];
    
    int *arrayRandoms = genera_lista_random(fp, numDatos);

    Persona *listaPersonas = malloc(sizeof(Persona)*numDatos);

    for(i=0; cantLeidos < numDatos; i++){
        fscanf(fp,"%[^\n]\n", buffer);
        if(i == arrayRandoms[cantLeidos]){
            listaPersonas[cantLeidos].edad = (rand() % 100) + 1;
            listaPersonas[cantLeidos].nombre = malloc(sizeof(buffer));
            strcpy(listaPersonas[cantLeidos].nombre , buffer);
            cantLeidos++;
        }
    }
    fclose(fp);
    free(arrayRandoms);
    return listaPersonas;
}

void leer_archivo_paises(char *nombre, int numDatos, Persona *listaPersonas){
    int i, random;
    char buffer[200];
    FILE* fp = fopen(nombre, "r");
    int numLineas = contar_lineas(fp);
    char **arrayPaises = malloc(sizeof(char*) * numLineas);
    
    for(i = 0 ; (fscanf(fp, "%[^\n]\n", buffer) != EOF); ++i){
    
        arrayPaises[i] = malloc(sizeof(buffer));
        strcpy(arrayPaises[i], buffer);
    }
    for(i = 0; i < numDatos; i++){
        random = rand() % numLineas;
        listaPersonas[i].lugarDeNacimiento = malloc(sizeof(buffer));
        strcpy(listaPersonas[i].lugarDeNacimiento, arrayPaises[random]);
    }
    for(i = 0; i < numLineas; i++){
        free(arrayPaises[i]);
    }
    free(arrayPaises);
}

void liberar_personas(Persona *listaPersonas, int numDatos){
    int i;
    for(i=0; i < numDatos; i++){
        free(listaPersonas[i].nombre);
        free(listaPersonas[i].lugarDeNacimiento);
    }
    free(listaPersonas);
}







// writeOutput toma un puntero a un archivo, el arreglo que contiene la información de cada usuario,
// el largo de dicho arreglo y el arreglo de localidades retornado por mapLocalidades.
// Escribe la información de cada usuario en el archivo "Output.txt".
void write_output(char *nombreArchivo,Persona *listaPersonas, int numDatos){ 
    int i=0;
    FILE *fp = fopen(nombreArchivo, "w+");
    for(i = 0; i < numDatos; i++){
        fprintf(fp, "%s, %d, %s\n", listaPersonas[i].nombre, listaPersonas[i].edad, listaPersonas[i].lugarDeNacimiento);
    }
    fclose(fp);
}

int main(){
    srand (time(NULL));
    int i=0; //Debbug
    int numDatos, numLineas;
    printf("Ingrese el numero de datos a generar:\n");
    scanf("%d", &numDatos);
    Persona *listaPersonas;



    listaPersonas = leer_archivo_personas("nombres1.txt", numDatos);

    leer_archivo_paises("paises.txt", numDatos, listaPersonas);

    write_output("output.txt",listaPersonas, numDatos);


    liberar_personas(listaPersonas, numDatos);
    
    return 0;
}