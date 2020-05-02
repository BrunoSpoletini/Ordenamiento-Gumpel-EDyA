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

void imprimir_dlist_archivo(DList* lista, FILE *fp, FuncionEscritura escribir_persona) {
  for (DNodo *nodo = lista->primero; nodo != NULL; nodo = nodo->sig){
    escribir_persona(nodo->dato, fp);
  }
}

void intercambiar_dato(DNodo* nodo1, DNodo* nodo2) {
  DNodo* aux = malloc(sizeof(DNodo));

  aux->dato = nodo1->dato;
  nodo1->dato = nodo2->dato;
  nodo2->dato = aux->dato;

  free(aux);
}

void mover_a_izquierda_de(DList* lista, DNodo* nodoPivote, DNodo* nodoAInsertar) {

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

DNodo* dividir_lista(DNodo* primero) { 
  DNodo *saltoDe2 = primero;
  DNodo *saltoDe1 = primero;

  while (saltoDe2->sig && saltoDe2->sig->sig) { 
    saltoDe2 = saltoDe2->sig->sig; 
    saltoDe1 = saltoDe1->sig; 
  } 
  DNodo *mitad = saltoDe1->sig;
  saltoDe1->sig = NULL;

  return mitad; 
} 

DNodo* merge(DNodo* primero, DNodo* segundo, Compara comparar) {  
  if (primero == NULL)  
    return segundo;  
  
  if (segundo == NULL)  
    return primero;  
  
  if (comparar(primero->dato, segundo->dato) < 0) {  
    primero->sig = merge(primero->sig, segundo, comparar);  
    primero->sig->ant = primero;  
    primero->ant = NULL;  
    return primero;  
  } else {  
    segundo->sig = merge(primero, segundo->sig, comparar);  
    segundo->sig->ant = segundo;  
    segundo->ant = NULL;  
    return segundo;  
  }  
}  
  
DNodo* merge_sort(DNodo* primero, Compara comparar) {
  if (primero == NULL || primero->sig == NULL)
    return primero;   
    
  DNodo *mitad = dividir_lista(primero);  
  
  primero = merge_sort(primero, comparar);  
  mitad = merge_sort(mitad, comparar);  
  
  return merge(primero, mitad, comparar);  
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
    intercambiar_dato(nodo1, menor);
  }

  return lista;
}

DList* dlist_insertion_sort(DList* lista, Compara comparar) {
  DNodo *nodoAComparar, *nodoMovil, *aux;
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

  return lista;
}

DList* dlist_merge_sort(DList* lista, Compara comparar) { 

  DNodo *nodo = lista->primero;

  nodo = merge_sort(nodo, comparar);  

  lista->primero = nodo;

  for (;nodo->sig != NULL;nodo = nodo->sig) //Este for tiene como funcion encontrar el final de la lista

  lista->ultimo = nodo;

  return lista;
}

DList* dlist_copia(DList* lista) {
  DList* copiaLista = dlist_crear();

  for (DNodo *nodo = lista->primero; nodo != NULL; nodo = nodo->sig) {
    dlist_agregar_final(copiaLista, nodo->dato);
  }

  return copiaLista;
}

void dlist_destruir_copia(DList* lista) {
  DNodo *nodoAEliminar;

  while (lista->primero != NULL) {
    nodoAEliminar = lista->primero;
    lista->primero = nodoAEliminar->sig;
    free(nodoAEliminar);
  }
  free(lista);
}

void dlist_ordenar_lista(DList* lista, TipoDeOrdenamiento algoritmo, Compara compara, char* output, FuncionEscritura escribir) {
  DList* copiaLista = dlist_copia(lista);
  clock_t tiempo = clock();

  copiaLista = algoritmo(copiaLista, compara);
  tiempo = clock() - tiempo;
  double tiempoSegundos = ((double)tiempo)/CLOCKS_PER_SEC;

  FILE* fp = fopen(output, "w+");
  fprintf(fp, "Tiempo: %lf\n\n", tiempoSegundos);
  imprimir_dlist_archivo(copiaLista, fp, escribir);
  fclose(fp);

  dlist_destruir_copia(copiaLista);
}