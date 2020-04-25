#ifndef __DLIST_H__
#define __DLIST_H__

#include <stddef.h>
#include <stdio.h>

#define TAM_LINEA 200

typedef struct {
char *nombre;
int edad;
char *lugarDeNacimiento; // pais o capital
} Persona;

typedef void (*FuncionVisitante) (void* dato); 

typedef void (*FuncionEscritura) (void* dato1, FILE* fp);

typedef int (*Compara) (void* dato1, void* dato2);

typedef struct _DNodo{
  void *dato ;
  //Persona dato; Esto es lo que estaba antes, pero no sirve ya que la estructura de listas pierde generalidad
  struct _DNodo *ant;
  struct _DNodo *sig;
} DNodo;

typedef struct {
  DNodo *primero;
  DNodo *ultimo;
} DList;

/**
 * Devuelve una lista vacía.
 */
DList* dlist_crear();

/**
 * Destruccion de la lista.
 */
void dlist_destruir(DList* lista, FuncionVisitante liberar);

/**
 * Determina si la lista es vacía.
 */
int dlist_vacia(DList* lista);

/**
 * Agrega un elemento al final de la lista.
 */
DList* dlist_agregar_final(DList* lista, void *dato);

/**
 * Agrega un elemento al inicio de la lista.
 */
DList* dlist_agregar_inicio(DList* lista, void *dato);

/**
 * Recorrido de la lista, utilizando la funcion pasada.
 */
void dlist_recorrer(DList* lista, FuncionVisitante imprimir_persona);

void imprimir_dlist_archivo(DList* lista, char *output, FuncionEscritura escribir_persona);

#endif /* __DLIST_H__ */
