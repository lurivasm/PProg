interface.o:	interface.c rectangles.c
	gcc -std=c99 -c -g interface.c


prueba.o: prueba.c lucia.c interface.c rectangles.c
		gcc -std=c99 -c -g prueba.c

rectangles.o:	rectangles.c
	gcc -std=c99 -c -g rectangles.c

lucia.o:	lucia.c interface.c rectangles.c
	gcc -std=c99 -c -g lucia.c

all:	interface.o rectangles.o lucia.o prueba.o
	gcc -pthread -o  prueba interface.o prueba.o rectangles.o lucia.o

clean:
	rm *.o
