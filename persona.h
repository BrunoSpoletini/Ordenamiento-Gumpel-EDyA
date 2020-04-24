#ifndef __PERSONA_H__
#define __PERSONA_H__

#include <stddef.h>

#define TAM_LINEA 200

// Dado un puntero a un archivo, devuelve la cantidad de lineas escritas.
// contar_lineas: FILE* -> int.
int contar_lineas(FILE* fp);

// greater_equal es una función de comparación entre dos enteros, 
// que retorna un entero mayor o igual a 0 si a<=b, o un entero negativo si a > b.
int greater_equal(const void *a, const void *b);



//void generar_personas (char* archivoPersonas, char* archivoPaises, char* archivoSalida, int cantDatos);



#endif