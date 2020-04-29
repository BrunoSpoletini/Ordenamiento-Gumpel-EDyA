#include "persona.h"

Persona* persona_crear(char* nombre, int edad, char* lugarDeNacimiento) {
  Persona* persona = (Persona*) malloc(sizeof(Persona));
  persona->nombre = malloc(sizeof(char) * (strlen(nombre)+1));
  strcpy(persona->nombre, nombre);
  persona->edad = edad;
  persona->lugarDeNacimiento = malloc(sizeof(char) * (strlen(lugarDeNacimiento)+1));
  strcpy(persona->lugarDeNacimiento, lugarDeNacimiento);
  return persona;
}

void imprimir_persona(void* persona) {
  printf("Nombre: %s, Edad: %d, Pais: %s\n", ((Persona*)persona)->nombre, ((Persona*)persona)->edad, ((Persona*)persona)->lugarDeNacimiento);
}

void escribir_persona(void* persona, FILE* fp) {
  fprintf(fp, "Nombre: %s, Edad: %d, Pais: %s\n", ((Persona*)persona)->nombre, ((Persona*)persona)->edad, ((Persona*)persona)->lugarDeNacimiento);
}

int compara_por_edad(void* dato1, void* dato2) {
  return ((Persona*)dato1)->edad - ((Persona*)dato2)->edad;
}

int compara_por_localidad(void* dato1, void* dato2) {
  return strcmp(((Persona*)dato1)->lugarDeNacimiento, ((Persona*)dato2)->lugarDeNacimiento);
}

void liberar_persona(void* persona) {
  free(((Persona*)persona)->lugarDeNacimiento);
  free(((Persona*)persona)->nombre);
  free((Persona*)persona);
}