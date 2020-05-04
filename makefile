TEMP = primeraParte/funcgenerarpersonas.o segundaParte/DList/dlist.o segundaParte/Persona/persona.o
ARG = -Wall -Wextra -Werror -std=c99

PP = primeraParte
FUNP = funcgenerarpersonas
GENP = generarpersonas

SP = segundaParte
LENL = listaenlazada
PER = persona
DPER = Persona
DLI = dlist
DDLI = DList

all: ejecutablePersona ejecutableListas

#Generar personas - Primera Parte
ejecutablePersona: $(PP)/$(FUNP).o $(PP)/$(GENP).c
	gcc $(ARG) -o ejecutablePersona $(PP)/$(GENP).c $(PP)/$(FUNP).o

funcgenerarpersonas.o: $(PP)/$(FUNP).c $(PP)/$(FUNP).h
	gcc $(ARG) -c $(PP)/$(FUNP).c
  
#Ordenar listas - Segunda parte
ejecutableListas: $(SP)/$(DDLI)/$(DLI).o $(SP)/$(DPER)/$(PER).o $(SP)/$(LENL).c
	gcc $(ARG) -o ejecutableListas $(SP)/$(LENL).c $(SP)/$(DDLI)/$(DLI).o $(SP)/$(DPER)/$(PER).o

dlist.o: $(SP)/$(DDLI)/$(DLI).c
	gcc $(ARG) -c $(SP)/$(DDLI)/$(DLI).c

persona.o: $(SP)/$(DPER)/$(PER).c
	gcc $(ARG) -c $(SP)/$(DPER)/$(PER).c

clean:
	-rm $(TEMP)

.PHONY : all
.PHONY : clean
