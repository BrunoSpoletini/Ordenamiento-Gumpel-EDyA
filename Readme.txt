gcc -c .\funcgenerarpersonas.c
gcc -o generarpersonas generarpersonas.c funcgenerarpersonas.o

gcc -c .\dlist.c 
gcc -o listaenlazada listaenlazada.c .\dlist.o