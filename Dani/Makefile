interface.o:	interface.c rectangles.c
	gcc -std=c99 -c -g interface.c


prueba.o: prueba.c dani.c interface.c rectangles.c
		gcc -std=c99 -c -g prueba.c

rectangles.o:	rectangles.c
	gcc -std=c99 -c -g rectangles.c

dani.o:	dani.c interface.c rectangles.c
	gcc -std=c99 -c -g dani.c

all:	interface.o rectangles.o dani.o prueba.o
	gcc -pthread -o  prueba interface.o prueba.o rectangles.o dani.o

clean:
	rm *.o
