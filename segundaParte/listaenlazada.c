#include "./DList/dlist.h"
#include "./Persona/persona.h"

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

  leer_archivo_personas(argv[1], lista);

  dlist_ordenar_lista(lista, dlist_selection_sort, compara_por_edad, "./segundaParte/sortedLists/selection_sort_edad.txt", escribir_persona);

  dlist_ordenar_lista(lista, dlist_selection_sort, compara_por_localidad, "./segundaParte/sortedLists/selection_sort_loc.txt", escribir_persona);

  dlist_ordenar_lista(lista, dlist_insertion_sort, compara_por_edad, "./segundaParte/sortedLists/insertion_sort_edad.txt", escribir_persona);
  
  dlist_ordenar_lista(lista, dlist_insertion_sort, compara_por_localidad, "./segundaParte/sortedLists/insertion_sort_loc.txt", escribir_persona);

  dlist_ordenar_lista(lista, dlist_merge_sort, compara_por_edad, "./segundaParte/sortedLists/merge_sort_edad.txt", escribir_persona);

  dlist_ordenar_lista(lista, dlist_merge_sort, compara_por_localidad, "./segundaParte/sortedLists/merge_sort_loc.txt", escribir_persona);

  dlist_destruir(lista, liberar_persona);
  printf("TERMINO\n");
  //printf("hola");
  return 0;
}
