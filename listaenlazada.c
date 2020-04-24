#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dlist.h"

static void imprimir_persona(Persona persona) {
  printf("Nombre: %s, Edad: %d, Pais: %s\n", persona.nombre, persona.edad, persona.lugarDeNacimiento);
}

void leer_archivo_personas(char *nombreArchivo, DList* lista){
    Persona persona;
    int edad;
    char nombre[TAM_LINEA], lugarDeNacimiento[TAM_LINEA];

    FILE* fp = fopen(nombreArchivo, "r");

    while(fscanf(fp, "%[^,], %d, %[^\n]\n", nombre, &edad, lugarDeNacimiento) != EOF){
      persona.nombre = malloc(sizeof(nombre));
      strcpy(persona.nombre, nombre);
      persona.edad = edad;
      persona.lugarDeNacimiento = malloc(sizeof(lugarDeNacimiento));
      strcpy(persona.lugarDeNacimiento, lugarDeNacimiento);

      lista = dlist_agregar_final(lista, persona);
    }
}

int main(int argc, char *argv[]) {

  DList* lista = dlist_crear();

  leer_archivo_personas("output.txt", lista);

  dlist_recorrer(lista, imprimir_persona);
  puts("");

  FILE *puntSalida = fopen("linked.txt", "w+");
  imprimir_dlist_archivo(lista, puntSalida);
  fclose(puntSalida);

  dlist_destruir(lista);

  printf("ok");

  return 0;
}
