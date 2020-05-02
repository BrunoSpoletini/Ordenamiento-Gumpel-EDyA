TEMP = primeraParte/funcgenerarpersonas.o segundaParte/DList/dlist.o segundaParte/Persona/persona.o


all: ejecutablePersona ejecutableListas

#Generar personas - Primera Parte
ejecutablePersona: primeraParte/funcgenerarpersonas.o primeraParte/generarpersonas.c
	gcc -o ejecutablePersona primeraParte/generarpersonas.c primeraParte/funcgenerarpersonas.o


funcgenerarpersonas.o: primeraParte/funcgenerarpersonas.c primeraParte/funcgenerarpersonas.h
	gcc -c primeraParte/funcgenerarpersonas.c
    

#Ordenar listas - Segunda parte
ejecutableListas: segundaParte/DList/dlist.o segundaParte/Persona/persona.o
	gcc -o ejecutableListas segundaParte/listaenlazada.c segundaParte/DList/dlist.o segundaParte/Persona/persona.o

dlist.o: segundaParte/DList/dlist.c
	gcc -c segundaParte/DList/dlist.c

persona.o: segundaParte/Persona/persona.c
	gcc -c segundaParte/Persona/persona.c

clean:
	-rm $(TEMP)

.PHONY : all
.PHONY : clean