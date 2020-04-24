gcc -c .\persona.c
gcc -o generarpersona generarpersona.c persona.o

gcc -c .\dlist.c 
gcc -o listaenlazada listaenlazada.c .\dlist.o