#ifndef __FUNCGENERARPERSONAS_H__
#define __FUNCGENERARPERSONAS_H__

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>

#define TAM_LINEA 200

// Dado un puntero a un archivo, devuelve la cantidad de lineas escritas.
// contar_lineas: FILE* -> int.
int contar_lineas(FILE* fp);

// greater_equal es una función de comparación entre dos enteros, 
// que retorna un entero mayor o igual a 0 si a<=b, o un entero negativo si a > b.
int greater_equal(const void *a, const void *b);

// Dados un puntero al archivo de personas y la cantidad de personas necesarias,
// devuelve un array con una cantidad de numeros random igual a la cantidad de personas necesarias,
// con el numero random siendo menor que la cantidad de nombres en el archivo.
// genera_lista_random: FILE*, int -> int*
int *genera_lista_random(FILE* puntPersonas, int cantDatos);

// Dados un puntero al archivo de paises y un puntero a la cantidad de paises,
// cuenta las lineas y lo guarda en numPaises y devuelve un array con los paises.
// leer_paises: FILE*, int* -> char**
char **leer_paises (char *archivoPaises, int *numPaises);

// Dados los punteros los archivos de: personas, paises y de salida, y la cantidad de personas necesarias,
// genera y escribe la cantidad de personas necesarias en el archivo de salida.
void generar_personas (char* archivoPersonas, char* archivoPaises, char* archivoSalida, int cantDatos);

#endif