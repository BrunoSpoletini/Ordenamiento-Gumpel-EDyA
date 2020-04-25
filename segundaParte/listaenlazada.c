#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dlist.h"

static void imprimir_persona(void* persona) {
  printf("Nombre: %s, Edad: %d, Pais: %s\n", ((Persona*)persona)->nombre, ((Persona*)persona)->edad, ((Persona*)persona)->lugarDeNacimiento);
}

static void liberar_persona(void* persona){
  free(((Persona*)persona)->lugarDeNacimiento);
  free(((Persona*)persona)->nombre);
  free((Persona*)persona);
}

static void leer_archivo_personas(char *nombreArchivo, DList* lista){
    Persona* persona;
    int edad;
    char nombre[TAM_LINEA], lugarDeNacimiento[TAM_LINEA];

    FILE* fp = fopen(nombreArchivo, "r");

    while(fscanf(fp, "%[^,], %d, %[^\n]\n", nombre, &edad, lugarDeNacimiento) != EOF){
      persona = malloc(sizeof(Persona));
      persona->nombre = malloc(sizeof(nombre));
      strcpy(persona->nombre, nombre);
      persona->edad = edad;
      persona->lugarDeNacimiento = malloc(sizeof(lugarDeNacimiento));
      strcpy(persona->lugarDeNacimiento, lugarDeNacimiento);

      lista = dlist_agregar_final(lista, (void*)persona);
    }
}

static void escribir_persona(void* persona, FILE* fp){
  fprintf(fp, "Nombre: %s, Edad: %d, Pais: %s\n", ((Persona*)persona)->nombre, ((Persona*)persona)->edad, ((Persona*)persona)->lugarDeNacimiento);
}

int main(int argc, char *argv[]) {

  DList* lista = dlist_crear();

  leer_archivo_personas("output.txt", lista);

  //dlist_recorrer(lista, imprimir_persona);
  //puts("");

  imprimir_dlist_archivo(lista, "linkedList.txt", escribir_persona);

  dlist_destruir(lista, liberar_persona);

  printf("ok");

  return 0;
}
