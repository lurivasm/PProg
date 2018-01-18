interface.o:	interface.c rectangles.c
	gcc -std=c99 -c -g interface.c


play.o: play.c dani.c blackjack.c card.c deck.c  world.c player.c  interface.c rectangles.c
		gcc -std=c99 -c -g play.c

rectangles.o:	rectangles.c
	gcc -std=c99 -c -g rectangles.c

dani.o:	dani.c interface.c rectangles.c
	gcc -std=c99 -c -g dani.c

blackjack.o: blackjack.c card.c deck.c interface.c rectangles.c
	gcc -std=c99 -c -g blackjack.c

card.o: card.c
	gcc -std=c99 -c -g card.c

deck.o: deck.c card.c
	gcc -std=c99 -c -g deck.c

world.o: world.c interface.c rectangles.c player.c
	gcc -std=c99 -c -g world.c

player.o: player.c
	gcc -std=c99 -c -g player.c


all:	interface.o rectangles.o dani.o play.o blackjack.o card.o deck.o world.o player.o
	gcc -pthread -o  play interface.o play.o rectangles.o dani.o blackjack.o card.o deck.o world.o player.o

clean:
	rm *.o
