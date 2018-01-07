interface.o:	interface.c rectangles.c
	gcc -std=c99 -c -g interface.c


prueba.o: prueba.c lucia.c interface.c rectangles.c
		gcc -std=c99 -c -g prueba.c

rectangles.o:	rectangles.c
	gcc -std=c99 -c -g rectangles.c

card.o:	card.c
		gcc -std=c99 -c -g card.c

deck.o: deck.c card.c
		gcc -std=c99 -c -g deck.c

lucia.o:	lucia.c interface.c rectangles.c card.c deck.c
	gcc -std=c99 -c -g lucia.c

all:	interface.o rectangles.o lucia.o prueba.o card.o deck.o
	gcc -pthread -o  prueba interface.o prueba.o rectangles.o lucia.o card.o deck.o

clean:
	rm *.o
