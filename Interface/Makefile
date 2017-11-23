


interface.o:	interface.c rectangles.c
	gcc -std=c99 -c -g interface.c


main.o:	main.c
	gcc -std=c99 -c -g main.c

rectangles.o:	rectangles.c
	gcc -std=c99 -c -g rectangles.c


all:	interface.o main.o rectangles.o
	gcc -o main interface.o main.o rectangles.o

clean:
	rm *.o
