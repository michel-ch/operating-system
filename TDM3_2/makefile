all: verif

verif: gestionFichiers.o verif.o
	gcc -o verif gestionFichiers.o verif.o

gestionFichiers.o: gestionFichiers.c
	gcc -c -Wall -ansi -pedantic gestionFichiers.c

verif.o: verif.c gestionFichiers.h
	gcc -c verif.c -W -Wall -ansi -pedantic

clean:
	rm -rf *.o *.exe