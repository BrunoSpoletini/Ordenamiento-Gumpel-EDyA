#include <stdio.h>
#include <stdlib.h>
//#include <math.h>
//#include <string.h>
//#include <time.h>

// contarLineas toma un puntero a un archivo
// Devuelve la cantidad de líneas que tiene ese archivo.
int contarLineas(FILE *fp){
  int count = 0;
  char buf[1010];
  while(fgets(buf,sizeof(buf), fp) != NULL){
    count++;
  }
  return count;
}

char **leerArchivos(FILE *fp, int *linesToRead, int lineasTotal, int max){
    int cantLeidos=0, i;
    
    char **stringList ,buffer[1010];
	stringList= malloc(sizeof(char*)*lineasTotal+1);
    for(i=1;i<=max && cantLeidos<lineasTotal;i++){
        fgets(buffer,1010,fp);
        if(i==linesToRead[cantLeidos]){
            stringList[cantLeidos]=malloc(sizeof(buffer));
            strcpy(stringList[cantLeidos],buffer);
            cantLeidos++;
        }
    }
    return stringList;
}


typedef struct {
char * nombre ;
int edad ;
char * lugarDeNacimiento ; // pais o capital
} Persona ;


int main(){
    int numDatos;
    printf("Ingrese el numero de datos a generar:\n");
    scanf("%d", &numDatos);
    Persona list = malloc(sizeof(Persona));

    return 0;
}