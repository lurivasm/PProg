
interface.o:	interface.c rectangles.c
	gcc -std=c99 -c -g interface.c


main.o:	main.c mane.c interface.c rectangles.c
	gcc -std=c99 -c -g main.c

rectangles.o:	rectangles.c
	gcc -std=c99 -c -g rectangles.c

mane.o:	mane.c interface.c rectangles.c
	gcc -std=c99 -c -g mane.c

all:	interface.o main.o rectangles.o mane.o
	gcc -o main interface.o main.o rectangles.o mane.o

clean:
	rm *.o