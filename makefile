TEMP = primeraParte/funcgenerarpersonas.o segundaParte/DList/dlist.o segundaParte/Persona/persona.o
ARG = -Wall -Wextra -Werror -std=c99

SALIDAPP = ejecutablePersona
SALIDASP = ejecutableListas

PP = primeraParte
FUNP = funcgenerarpersonas 
GENP = generarpersonas

SP = segundaParte
LENL = listaenlazada
PER = persona
DPER = Persona
DLI = dlist
DDLI = DList

all: $(SALIDASP) $(SALIDAPP)

#Generar personas - Primera Parte
$(SALIDAPP): $(PP)/$(FUNP).o $(PP)/$(GENP).c
	gcc $(ARG) -o $(SALIDAPP) $(PP)/$(GENP).c $(PP)/$(FUNP).o


funcgenerarpersonas.o: $(PP)/$(FUNP).c $(PP)/$(FUNP).h
	gcc $(ARG) -c $(PP)/$(FUNP).c
    

#Ordenar listas - Segunda parte
$(SALIDASP): $(SP)/$(DDLI)/$(DLI).o $(SP)/$(PER)/$(PER).o $(SP)/$(LENL).c
	gcc $(ARG) -o $(SALIDASP) $(SP)/$(LENL).c $(SP)/$(DDLI)/$(DLI).o $(SP)/$(PER)/$(PER).o

dlist.o: $(SP)/$(DDLI)/$(DLI).c
	gcc $(ARG) -c $(SP)/$(DDLI)/$(DLI).c

persona.o: $(SP)/$(PER)/$(PER).c
	gcc $(ARG) -c $(SP)/$(PER)/$(PER).c

clean:
	-rm $(TEMP)

.PHONY : all
.PHONY : clean