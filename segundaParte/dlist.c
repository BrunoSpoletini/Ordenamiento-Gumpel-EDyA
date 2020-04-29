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

void swap_dato(DNodo* lista1, DNodo* lista2) {
  DNodo* aux = malloc(sizeof(DNodo));
  aux->dato = lista1->dato;
  lista1->dato = lista2->dato;
  lista2->dato = aux->dato;
  free(aux);
}

void mover_a_izquierda_de(DList *lista, DNodo* nodoPivote, DNodo* nodoAInsertar) {

  if(nodoAInsertar->ant != NULL)
    (nodoAInsertar->ant)->sig = nodoAInsertar->sig;

  if(nodoAInsertar->sig != NULL)
    (nodoAInsertar->sig)->ant = nodoAInsertar->ant;

  else
    lista->ultimo = nodoAInsertar->ant;

  nodoAInsertar->sig = nodoPivote;
  nodoAInsertar->ant = nodoPivote->ant;

  if(nodoPivote->ant == NULL)
    lista->primero = nodoAInsertar;
  
  nodoPivote->ant = nodoAInsertar;

  if(nodoPivote->ant->ant != NULL)
    nodoPivote->ant->ant->sig = nodoAInsertar;
}

DList* dlist_selection_sort(DList* lista, Compara comparar){
  DNodo *menor;
  for (DNodo *nodo1 = lista->primero; nodo1 != NULL; nodo1 = nodo1->sig){
    menor = nodo1;
    for(DNodo *nodo2 = nodo1->sig; nodo2 != NULL; nodo2 = nodo2->sig){
      if(comparar(menor->dato, nodo2->dato) > 0){
        menor = nodo2;
      }
    }
    swap_dato(nodo1, menor);
  }
  return lista;
}

//Mover nodo delaante de(posPivot, nodoAMover)
DList* dlist_insertion_sort(DList* lista, Compara comparar) {
  DNodo *nodoAComparar, *nodoMovil, *aux = malloc(sizeof(DNodo));
  if (lista->primero == NULL || lista->primero->sig == NULL)
    return lista;

  aux = lista->primero->sig;
  nodoAComparar = aux;
  while (nodoAComparar != NULL) {
    nodoMovil = nodoAComparar;
    while ((nodoMovil->ant != NULL) && (comparar(nodoAComparar->dato, nodoMovil->ant->dato) < 0)) {
      nodoMovil = nodoMovil->ant;
    }
    aux = nodoAComparar->sig;
    if (nodoAComparar != nodoMovil) {
      mover_a_izquierda_de(lista, nodoMovil, nodoAComparar);
    }
    nodoAComparar = aux;
  }
  free(aux);
  return lista;
}

DNodo* nodo_medio(DList* lista) { 
    DNodo *saltoDe2 = lista->primero;
    DNodo *saltoDe1 = lista->primero;

    while (saltoDe2->sig && saltoDe2->sig->sig) { 
      saltoDe2 = saltoDe2->sig->sig; 
      saltoDe1 = saltoDe1->sig; 
    } 
    DNodo *mitad = saltoDe1->sig;

    return mitad; 
} 

DList* merge(DList* lista1, DList* lista2, Compara comparar) { 
    DList* mergedList = dlist_crear();

    if (lista1->primero == NULL)
      return lista2; 
  
    if (lista2->primero == NULL) 
      return lista1; 
  
    if (comparar(lista1->primero->dato, lista2->primero->dato) < 0) {
      mergedList->primero = lista1->primero;
      lista1->primero = lista1->primero->sig;   
      mergedList->primero->sig = merge(lista1,lista2, comparar)->primero;
      return mergedList; 

    } else { 
      mergedList->primero = lista2->primero;
      lista2->primero = lista2->primero->sig;   
      mergedList->primero->sig = merge(lista1,lista2, comparar)->primero;
      return mergedList;
    } 
} 
  
DList* dlist_merge_sort(DList* lista, Compara comparar) { 

    if (lista->primero == NULL || lista->primero->sig == NULL)
      return lista; 

    DNodo *mitad = nodo_medio(lista);
    DList *lista1 = malloc(sizeof(DList));
    DList *lista2 = malloc(sizeof(DList));

    lista1->primero = lista->primero;
    lista1->ultimo = mitad->ant;
    lista1->ultimo->sig = NULL;
    lista2->primero = mitad;
    lista2->ultimo = lista->ultimo;
    
    lista1 = dlist_merge_sort(lista1, comparar); 
    lista2 = dlist_merge_sort(lista2, comparar); 
  
    return merge(lista1, lista2, comparar); 
} 

/*/
DList* dlist_insertionSort (DList* lista, Compara comparar) {
    DNodo *sec_data = malloc(sizeof(DNodo));
    DNodo *temp = malloc(sizeof(DNodo));
    for (DNodo* t1 = lista->primero->sig; t1!= NULL; t1 = t1->sig) {
        sec_data->dato = t1->dato;
        int found = 0;
        DNodo* t2 = lista->primero;
        for (; t2 != t1; t2 = t2->sig) {
            if((comparar(t2->dato, t1->dato) > 0) && found == 0) {
                sec_data->dato = t2->dato;
                t2->dato = t1->dato;
                found = 1;
            } else if (found == 1) {
                    temp->dato = sec_data->dato;
                    sec_data->dato = t2->dato;
                    t2->dato = temp->dato;
            }
        }
        t2->dato = sec_data->dato;
    }
    return lista;
}/*/

/*/
GList glist_insertion_sort(GList list, Compare function) {
  if (list) {
    GNode* auxNode = list->next;
    do {
      GNode* node = auxNode->prev;
      for (; function(node->data, auxNode->data) > 0 && node != list->prev; node = node->prev);
      GNode* newLastPosition = auxNode->next;
      if (node != auxNode->prev) {
        node = node->next;
        if (node == list) {
          list = auxNode;
        }
        //Sacando node de su posicion
        auxNode->prev->next = auxNode->next;
        auxNode->next->prev = auxNode->prev;
        //Moviendo node a la izquierda de nodeHastaSwapear
        auxNode->next = node;
        auxNode->prev = node->prev;
        node->prev->next = auxNode;
        node->prev = auxNode;
      }
      auxNode = newLastPosition;
    } while (auxNode != list);
  }
  return list;
}/*/