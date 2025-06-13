all: transfer

transfer: gestionFichiers.o transfer.o
	gcc -o transfer gestionFichiers.o transfer.o

gestionFichiers.o: gestionFichiers.c
	gcc -c -Wall -ansi -pedantic gestionFichiers.c

transfer.o: transfer.c gestionFichiers.h
	gcc -c transfer.c -W -Wall -ansi -pedantic

clean:
	rm -rf *.o *.exe