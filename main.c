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

int main(){


    return 0;
}