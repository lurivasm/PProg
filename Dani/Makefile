MCC = gcc -ansi -pedantic -std=c99
CFLAGS = -Wall -g -std=c99 
EXE =  prueba



all : $(EXE)

clean :
	rm -f *.o core $(EXE)

$(EXE) : % : %.o dani.o interface.o rectangles.o
