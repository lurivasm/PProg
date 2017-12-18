MCC = gcc -ansi -pedantic -std=c99
CFLAGS = -Wall -g
EXE = main_titulo_Blackjack train



all : $(EXE)

clean :
	rm -f *.o core $(EXE)

$(EXE) : % : %.o card.o deck.o blackjack.o interface.o rectangles.o
