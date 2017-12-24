interface.o:	interface.c rectangles.c
	gcc -std=c99 -c -g interface.c


laser.o: laser.c dani.c interface.c rectangles.c
		gcc -std=c99 -c -g laser.c

rectangles.o:	rectangles.c
	gcc -std=c99 -c -g rectangles.c

dani.o:	dani.c interface.c rectangles.c
	gcc -std=c99 -c -g dani.c

all:	interface.o rectangles.o dani.o laser.o
	gcc -pthread -o  laser interface.o laser.o rectangles.o dani.o

clean:
	rm *.o
