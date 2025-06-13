all: transfer

transfer: transfer.o
	gcc -o transfer transfer.o

transfer.o: transfer.c gestionFichiers.h
	gcc -c transfer.c -W -Wall -ansi -pedantic

clean:
	rm -rf *.o *.exe