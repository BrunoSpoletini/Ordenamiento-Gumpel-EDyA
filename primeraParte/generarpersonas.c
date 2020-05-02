#include "funcgenerarpersonas.h"

int main (int argc, char *argv[]) {
  srand (time(NULL));
  generar_personas(argv[1], argv[2], argv[3], atoi(argv[4]));
  return 0;
}