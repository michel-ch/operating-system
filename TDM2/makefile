all: testIB1 testIB2 testIB3 source test2b1 testIII1 testIII2 testIII3

testIB1: character.o testIB1.o
	gcc -o testIB1 character.o testIB1.o
testIB2: character.o testIB2.o
	gcc -o testIB2 character.o testIB2.o
testIB3: character.o testIB3.o
	gcc -o testIB3 character.o testIB3.o
source: character.o source.o
	gcc -o source character.o source.o
test2b1: gestionFichiers.o test2b1.o
	gcc -o test2b1 gestionFichiers.o test2b1.o
testIII2: gestionFichiers.o testIII2.o
	gcc -o testIII2 gestionFichiers.o testIII2.o
testIII3: gestionFichiers.o testIII3.o
	gcc -o testIII3 gestionFichiers.o testIII3.o

character.o: character.c
	gcc -c -Wall -ansi -pedantic character.c
gestionFichiers.o: gestionFichiers.c
	gcc -c -Wall -ansi -pedantic gestionFichiers.c

testIB1.o: testIB1.c character.h
	gcc -c testIB1.c -W -Wall -ansi -pedantic
testIB2.o: testIB2.c character.h
	gcc -c testIB2.c -W -Wall -ansi -pedantic
testIB3.o: testIB3.c character.h
	gcc -c testIB3.c -W -Wall -ansi -pedantic
source.o: source.c character.h
	gcc -c source.c -W -Wall -ansi -pedantic
test2b1.o: test2b1.c gestionFichiers.h
	gcc -c test2b1.c -W -Wall -ansi -pedantic
testIII1.o: testIII1.c
	gcc -c testIII1.c -W -Wall -ansi -pedantic
testIII2.o: testIII2.c
	gcc -c testIII2.c -W -Wall -ansi -pedantic
testIII3.o: testIII3.c
	gcc -c testIII3.c -W -Wall -ansi -pedantic

clean:
	rm -rf *.o *.exe