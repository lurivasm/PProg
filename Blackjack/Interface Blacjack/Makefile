


interface.o:	interface.c rectangles.c
	gcc -std=c99 -c -g interface.c


main_titulo_Blackjack.o:	main_titulo_Blackjack.c
	gcc -std=c99 -c -g main_titulo_Blackjack.c

rectangles.o:	rectangles.c
	gcc -std=c99 -c -g rectangles.c


all:	interface.o main_titulo_Blackjack.o rectangles.o
	gcc -o main_titulo_Blackjack interface.o main_titulo_Blackjack.o rectangles.o

clean:
	rm *.o
