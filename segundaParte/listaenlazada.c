#include "../DList/dlist.h"
#include "../Persona/persona.h"

static void leer_archivo_personas(char *nombreArchivo, DList* lista) {
    Persona* persona;
    int edad;
    char nombre[TAM_BUFFER], lugarDeNacimiento[TAM_BUFFER];

    FILE* fp = fopen(nombreArchivo, "r");
    while (fscanf(fp, "%[^,], %d, %[^\n]\n", nombre, &edad, lugarDeNacimiento) != EOF) {
      persona = persona_crear(nombre, edad, lugarDeNacimiento);
      lista = dlist_agregar_final(lista, (void*)persona);
    }
}

int main(int argc, char *argv[]) {

  DList* lista = dlist_crear();

  leer_archivo_personas("output.txt", lista);

  //dlist_recorrer(lista, imprimir_persona);

  //lista = dlist_selection_sort (lista, compara_por_edad);

  //lista = dlist_insertion_sort (lista, compara_por_edad);

  lista = dlist_merge_sort (lista, compara_por_edad);

  //mover_a_izquierda_de(lista, lista->primero, lista->primero->sig->sig->sig);

  imprimir_dlist_archivo(lista, "linkedList.txt", escribir_persona);

  //dlist_recorrer(lista, imprimir_persona);
  //printf("hola");
  dlist_destruir(lista, liberar_persona);
  printf("TERMINO\n");
  //printf("hola");
  return 0;
}
