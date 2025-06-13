all: test1c test2b1 test2b2 test2b3 test2b4 test2b5 test3b1 test3b2 test3b3

test1c: gestionFichiers.o test1c.o
	gcc -o test1c gestionFichiers.o test1c.o
test2b1: gestionFichiers.o test2b1.o
	gcc -o test2b1 gestionFichiers.o test2b1.o
test2b2: gestionFichiers.o test2b2.o
	gcc -o test2b2 gestionFichiers.o test2b2.o
test2b3: gestionFichiers.o test2b3.o
	gcc -o test2b3 gestionFichiers.o test2b3.o
test2b4: gestionFichiers.o test2b4.o
	gcc -o test2b4 gestionFichiers.o test2b4.o
test2b5: gestionFichiers.o test2b5.o
	gcc -o test2b5 gestionFichiers.o test2b5.o
test3b1: gestionFichiers.o test3b1.o
	gcc -o test3b1 gestionFichiers.o test3b1.o
test3b2: gestionFichiers.o test3b2.o
	gcc -o test3b2 gestionFichiers.o test3b2.o
test3b3: gestionFichiers.o test3b3.o
	gcc -o test3b3 gestionFichiers.o test3b3.o

gestionFichiers.o: gestionFichiers.c
	gcc -c -Wall -ansi -pedantic gestionFichiers.c

test1c.o: test1c.c gestionFichiers.h
	gcc -c test1c.c -W -Wall -ansi -pedantic
test2b1.o: test2b1.c gestionFichiers.h
	gcc -c test2b1.c -W -Wall -ansi -pedantic
test2b2.o: test2b2.c gestionFichiers.h
	gcc -c test2b2.c -W -Wall -ansi -pedantic
test2b3.o: test2b3.c gestionFichiers.h
	gcc -c test2b3.c -W -Wall -ansi -pedantic
test2b4.o: test2b4.c gestionFichiers.h
	gcc -c test2b4.c -W -Wall -ansi -pedantic
test2b5.o: test2b5.c gestionFichiers.h
	gcc -c test2b5.c -W -Wall -ansi -pedantic
test3b1.o: test3b1.c gestionFichiers.h
	gcc -c test3b1.c -W -Wall -ansi -pedantic
test3b2.o: test3b2.c gestionFichiers.h
	gcc -c test3b2.c -W -Wall -ansi -pedantic
test3b3.o: test3b3.c gestionFichiers.h
	gcc -c test3b3.c -W -Wall -ansi -pedantic

clean:
	rm -rf *.o *.exe