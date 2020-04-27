#include "dlist.h"
#include <stdlib.h>

DList* dlist_crear() {
  DList *lista = malloc(sizeof(DList));
  lista->primero = NULL;
  lista->ultimo = NULL;
  return lista;
}

void dlist_destruir(DList* lista, FuncionVisitante liberar) {
  DNodo *nodoAEliminar;
  while (lista->primero != NULL) {
    nodoAEliminar = lista->primero;
    lista->primero = nodoAEliminar->sig;
    liberar(nodoAEliminar->dato);
    free(nodoAEliminar);
  }
  free(lista);
}

int dlist_vacia(DList* lista) {
  return lista == NULL;
}

DList* dlist_agregar_final(DList* lista, void* dato) {
  DNodo *nuevoNodo = malloc(sizeof(DNodo));
  nuevoNodo->dato = dato;
  nuevoNodo->sig = NULL;
  nuevoNodo->ant = lista->ultimo;

  if (lista->ultimo != NULL){
    lista->ultimo->sig = nuevoNodo;
  }
  if (lista->primero == NULL){
    lista->primero = nuevoNodo;
  }
  lista->ultimo = nuevoNodo;
  return lista;
}

DList* dlist_agregar_inicio(DList* lista, void* dato) {
  DNodo *nuevoNodo = malloc(sizeof(DNodo));
  nuevoNodo->dato = dato;
  nuevoNodo->sig = lista->primero;
  nuevoNodo->ant = NULL;
  if (lista->primero != NULL){
    lista->primero->ant = nuevoNodo;
  }
  if (lista->ultimo == NULL){
    lista->ultimo = nuevoNodo;
  }
  lista->primero = nuevoNodo;
  return lista;
}

void dlist_recorrer(DList* lista, FuncionVisitante imprimir_persona) {
  for (DNodo *nodo = lista->primero; nodo != NULL; nodo = nodo->sig)
    imprimir_persona(nodo->dato);
}

void imprimir_dlist_archivo(DList* lista, char *output, FuncionEscritura escribir_persona) {
  FILE *fp = fopen(output, "w+");
  for (DNodo *nodo = lista->primero; nodo != NULL; nodo = nodo->sig){
    escribir_persona(nodo->dato, fp);
  }
  fclose(fp);
}

DList* dlist_selectionSort (DList* lista, Compara comparar){
  DNodo *menor, *aux = malloc(sizeof(DNodo));
  for (DNodo *nodo1 = lista->primero; nodo1 != NULL; nodo1 = nodo1->sig){
    menor = nodo1;
    for(DNodo *nodo2 = nodo1->sig; nodo2 != NULL; nodo2 = nodo2->sig){
      if(comparar(menor->dato, nodo2->dato) > 0){
        menor = nodo2;
      }
    }
    aux->dato = nodo1->dato;
    nodo1->dato = menor->dato;
    menor->dato = aux->dato;
  }
  free(aux);
  return lista;
}

DList* dlist_insertionSort (DList* lista, Compara comparar){
  DNodo *nodoAComparar;
  DNodo *nodoMovil;
  nodoAComparar = lista->ultimo;
  while(nodoAComparar != NULL){
    printf("hi");
    
    nodoMovil = nodoAComparar->ant;
    while((nodoMovil != NULL) && (comparar(nodoAComparar->dato, nodoMovil->dato) > 0)){
      nodoMovil = nodoMovil->ant;
    }
    printf("hi");
    nodoAComparar->ant = nodoMovil;
    nodoAComparar->sig = nodoMovil->sig;
    nodoMovil->sig->ant = nodoAComparar;
    nodoMovil->sig = nodoAComparar;

    nodoAComparar = nodoAComparar->ant;
  }

  return lista;
}


//DList* dlist_mergeSort (DList* lista, Compara comparar)
