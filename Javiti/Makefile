CC = gcc
CFLAGS = -Wall -Wextra -pedantic -ansi


EXE = prueba

all : $(EXE)

clean :
	rm -f *.o core $(EXE)

$(EXE) : % : %.o javiti.o rectangles.o interface.o
