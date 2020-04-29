#ifndef __DLIST_H__
#define __DLIST_H__

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

typedef void (*FuncionVisitante) (void* dato); 

typedef void (*FuncionEscritura) (void* dato1, FILE* fp);

typedef int (*Compara) (void* dato1, void* dato2);

typedef struct _DNodo{
  void *dato ;
  struct _DNodo *ant;
  struct _DNodo *sig;
} DNodo;

typedef struct {
  DNodo *primero;
  DNodo *ultimo;
} DList;

//  Devuelve una lista vacía.
DList* dlist_crear();

//  Destruccion de la lista.
void dlist_destruir(DList* lista, FuncionVisitante liberar);

//  Determina si la lista es vacía.
int dlist_vacia(DList* lista);

//  Agrega un elemento al final de la lista.
DList* dlist_agregar_final(DList* lista, void *dato);

//  Agrega un elemento al inicio de la lista.
DList* dlist_agregar_inicio(DList* lista, void *dato);  // inutil?

//  Recorrido de la lista, utilizando la funcion pasada.
void dlist_recorrer(DList* lista, FuncionVisitante imprimir_persona); // testeo inutil?

//  Dados un dlist, un archivo, y una funcion, 
//  escribe la persona en el archivo correspondiente utilizando la funcion.
void imprimir_dlist_archivo(DList* lista, char *output, FuncionEscritura escribir_persona);

//  Dados 2 nodos, intercambia sus datos
void swap_dato(DNodo* nodo1, DNodo* nodo2);

//  Dados un dlist, un nodo a insertar y un nodo pivote, 
//  coloca el nodo a insertar a la izquierda del pivote.
void mover_a_izquierda_de(DList *lista, DNodo* nodoAInsertar, DNodo* nodoPivote);

//  Dada una dlist, devuelve el nodo que seria su mitad.
DNodo* nodo_medio(DList* lista);

//  Dadas 2 dlist y una funcion de comparacion,
//  devuelve una dlist union de ambas ordenadas mediante la funcion.
DList* merge(DList* lista1, DList* lista2, Compara comparar);

//  Dadas una dlist y una funcion de comparacion,
//  devuelve una dlist ordenada por selection sort mediante esa funcion
DList* dlist_selection_sort (DList* lista, Compara comparar);

//  Dadas una dlist y una funcion de comparacion,
//  devuelve una dlist ordenada por insertion sort mediante esa funcion
DList* dlist_insertion_sort (DList* lista, Compara comparar);

//  Dadas una dlist y una funcion de comparacion,
//  devuelve una dlist ordenada por merge sort mediante esa funcion
DList* dlist_merge_sort(DList* lista, Compara comparar);

#endif /* __DLIST_H__ */
