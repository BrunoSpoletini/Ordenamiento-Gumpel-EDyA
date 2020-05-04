#ifndef __PERSONA_H__
#define __PERSONA_H__

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define TAM_BUFFER 100

typedef struct {
char *nombre;
int edad;
char *lugarDeNacimiento;
} Persona;

//  Dados el nombre, la edad y el lugar de nacimiento, crea una persona con estos datos,
//  y devuelve un puntero a esta persona.
//  persona_crear: char* int char* -> Persona*
Persona* persona_crear(char* nombre, int edad, char* lugarDeNacimiento);

//  Dados una persona y un archivo, escribe la persona en el archivo correspondiente.
void escribir_persona(void* persona, FILE* fp);

//  Dadas dos personas compara sus edades y devuelve:
//  0 si son iguales.
//  Un numero mayor a 0 si la edad de la primera es mayor que de la segunda.
//  Un numero menor a 0 si la edad de la primera es menor que de la segunda.
//  compara_por_edad: void* void* -> int
int compara_por_edad(void* dato1, void* dato2);

//  Dadas dos personas compara sus lugares de nacimiento y devuelve:
//  0 si son iguales.
//  Un numero mayor a 0 si el lugar de nacimiento de la primera tiene mayor valor ASCII que de la segunda.
//  Un numero menor a 0 si el lugar de nacimiento de la primera tiene menor valor ASCII que de la segunda.
//  compara_por_localidad: void* void* -> int
int compara_por_localidad(void* dato1, void* dato2);

// Dada una persona, libera la memoria ocupada por esta.
void liberar_persona(void* persona);


#endif /* __PERSONA_H__ */