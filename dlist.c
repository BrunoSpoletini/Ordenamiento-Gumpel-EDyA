#include "dlist.h"
#include <stdlib.h>

DList* dlist_crear() {
  DList *lista = malloc(sizeof(DList));
  lista->primero = NULL;
  lista->ultimo = NULL;
  return lista;
}

void dlist_destruir(DList* lista) {
  DNodo *nodoAEliminar;
  while (lista->primero != NULL) {
    nodoAEliminar = lista->primero;
    lista->primero = nodoAEliminar->sig;
    free(nodoAEliminar->dato.nombre);
    free(nodoAEliminar->dato.lugarDeNacimiento);
    free(nodoAEliminar);
  }
}

int dlist_vacia(DList* lista) {
  return lista == NULL;
}

DList* dlist_agregar_final(DList* lista, Persona dato) {
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

DList* dlist_agregar_inicio(DList* lista, Persona dato) {
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

void dlist_recorrer(DList* lista, FuncionVisitante visit) {
  for (DNodo *nodo = lista->primero; nodo != NULL; nodo = nodo->sig)
    visit(nodo->dato);
}

void imprimir_dlist_archivo(DList* lista, FILE* fp) {
  for (DNodo *nodo = lista->primero; nodo != NULL; nodo = nodo->sig){
    fprintf(fp, "Nombre: %s, Edad: %d, Pais: %s\n", nodo->dato.nombre, nodo->dato.edad, nodo->dato.lugarDeNacimiento);
  }
}

