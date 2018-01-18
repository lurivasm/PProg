MCC = gcc -ansi -pedantic -std=c99
CFLAGS = -Wall -g -std=c99
EXE = play



all : $(EXE)

clean :
	rm -f *.o core $(EXE)

$(EXE) : % : %.o card.o deck.o blackjack.o interface.o rectangles.o
