
interface.o:	interface.c rectangles.c
	gcc -std=c99 -c -g interface.c


main.o:	main.c luis.c interface.c rectangles.c
	gcc -std=c99 -c -g main.c

rectangles.o:	rectangles.c
	gcc -std=c99 -c -g rectangles.c

luis.o:	luis.c interface.c rectangles.c
	gcc -std=c99 -c -g luis.c

all:	interface.o main.o rectangles.o luis.o
	gcc -pthread -o main interface.o main.o rectangles.o luis.o

clean:
	rm *.o
