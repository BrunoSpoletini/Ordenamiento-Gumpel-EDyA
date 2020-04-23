#include <stdio.h>
#include <stdlib.h>
#include "dlist.h"

static void imprimir_entero(int dato) {
  printf("%d ", dato);
}

int main(int argc, char *argv[]) {

  DList* lista = dlist_crear();

  lista = dlist_agregar_inicio(lista, 3);
  lista = dlist_agregar_inicio(lista, 2);
  lista = dlist_agregar_inicio(lista, 1);
  lista = dlist_agregar_final(lista, 4);

  dlist_recorrer(lista, imprimir_entero);
  puts("");

  dlist_destruir(lista);

  printf("ok");

  return 0;
}
