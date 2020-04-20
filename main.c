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
    random = rand() % (numLineas-i);
    arrayRandoms[i]=random;
    arrayContinuo[random]=arrayContinuo[numLineas-i];
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
/*/
void leer_archivo_paises(char *nombre, int numDatos, Persona *listaPersonas){
    int i;
    FILE* fp = fopen(nombre, "r");
    int numLineas = contar_lineas(fp);

    for(i = 0 ; (fscanf(fp, "%[^\n]\n", linea) != EOF); ++i){ // Mientras la linea no este vacia
        strcpy(arrayPaises[i],linea); // Coloca la linea en la matriz
        }
    
}/*/

void liberar_personas(Persona *listaPersonas, int numDatos){
    int i;
    for(i=0; i < numDatos; i++){
        free(listaPersonas[i].nombre);
        //free(listaPersonas[i].lugarDeNacimiento); descomentar luego de asignarle localidad a las personas
    }
    free(listaPersonas);
}

int main(){
    srand (time(NULL));
    int i=0; //Debbug
    int numDatos, numLineas;
    printf("Ingrese el numero de datos a generar:\n");
    scanf("%d", &numDatos);
    Persona *listaPersonas;


    

    listaPersonas = leer_archivo_personas("nombres1.txt", numDatos);

    //listaPersonas = leer_archivo_paises("paises.txt", numDatos, listaPersonas);

    

    //debbug
    for(i=0;i<numDatos;i++){
    printf("%s\n",listaPersonas[i].nombre);
    }
    
    liberar_personas(listaPersonas, numDatos);
    
    return 0;
}