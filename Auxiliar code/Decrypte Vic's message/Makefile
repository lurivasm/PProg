CC = gcc
CFLAGS = -Wall -Wextra -pedantic -ansi


EXE = vic

all : $(EXE)

clean :
	rm -f *.o core $(EXE)

$(EXE) : % : %.o message.o rectangles.o interface.o
