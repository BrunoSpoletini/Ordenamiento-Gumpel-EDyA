gcc -c .\persona.c
gcc -o generarpersonas generarpersonas.c persona.o

gcc -c .\dlist.c 
gcc -o listaenlazada listaenlazada.c .\dlist.o