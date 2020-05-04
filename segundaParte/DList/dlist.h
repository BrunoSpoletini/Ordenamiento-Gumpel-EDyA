#ifndef __DLIST_H__
#define __DLIST_H__

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
    typedef struct _DNodo {
  void *dato;
   struct _DNodo *ant;
  struct _DNodo *sig;
} DNodo;
 typedef struct {
  DNodo * primero;
  DNodo * ultimo;
} DList;
 typedef void (*FuncionVisitante) (void *dato);
 typedef void (*FuncionEscritura) (void *dato1, FILE * fp);
 typedef int (*Compara) (void *dato1, void *dato2);
 typedef DList *(*TipoDeOrdenamiento) (DList * lista, Compara funcion);
 
//  Devuelve una lista vacía.
    DList * dlist_crear();
 
//  Destruccion de la lista.
void dlist_destruir(DList * lista, FuncionVisitante liberar);
 
//  Agrega un elemento al final de la lista.
    DList * dlist_agregar_final(DList * lista, void *dato);
 
//  Dados un dlist, un archivo, y una funcion, 
//  escribe la persona en el archivo correspondiente utilizando la funcion.
void imprimir_dlist_archivo(DList * lista, FILE * fp,
                            FuncionEscritura escribir_persona);
 
//  Dados 2 nodos, intercambia sus datos.
void intercambiar_dato(DNodo * nodo1, DNodo * nodo2);
 
//  Dados un dlist, un nodo a insertar y un nodo pivote, 
//  coloca el nodo a insertar a la izquierda del pivote.
void mover_a_izquierda_de(DList * lista, DNodo * nodoAInsertar,
                          DNodo * nodoPivote);
 
//  Dado el primer nodo de la lista, devuelve el nodo de la mitad de la lista,
//  y corta su ruta al anterior, dividiendo la lista en 2 partes.
    DNodo * dividir_lista(DNodo * primero);
 
// Dado el primer nodo de la lista y el primer nodo de otra lista,
// une las dos listas ordenadamente y devuelve el primer nodo de esta.
    DNodo * merge(DNodo * primero, DNodo * segundo, Compara comparar);
 
// Dado el primer nodo de la lista, la ordena recursivamente y 
// devuelve el primer nodo de esta lista ordenada.
    DNodo * merge_sort(DNodo * primero, Compara comparar);
 
//  Dadas una dlist y una funcion de comparacion,
//  devuelve una dlist ordenada por selection sort mediante esa funcion
    DList * dlist_selection_sort(DList * lista, Compara comparar);
 
//  Dadas una dlist y una funcion de comparacion,
//  devuelve una dlist ordenada por insertion sort mediante esa funcion.
    DList * dlist_insertion_sort(DList * lista, Compara comparar);
 
//  Dadas una dlist y una funcion de comparacion,
//  devuelve una dlist ordenada por merge sort mediante esa funcion.
    DList * dlist_merge_sort(DList * lista, Compara comparar);
 
//  Dada una dlist, crea una copia de esta con los mismos datos
//  y devuelve una dlist.
    DList * dlist_copia(DList * lista);
 
//  Dada una dlist, destruye los nodos de la lista sin liberar los datos de los nodos.
void dlist_destruir_copia(DList * lista);
 
//  Dadas una dlist, un tipo de ordenamiento, una funcion de comparacion, el nombre de un archivo de salida y una funcion para escribir,
//  crea una copia de la lista, le aplica el algoritmo y la imprime en un archivo con el tiempo que tardo en ejecutarse.
void dlist_ordenar_lista(DList * lista, TipoDeOrdenamiento algoritmo,
                         Compara compara, char *output,
                         FuncionEscritura escribir);
 
#endif  /* __DLIST_H__ */
