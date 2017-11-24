#ifndef INTERFACE_H
#define INTERFACE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <time.h>
#include <unistd.h>


#include <termios.h>
#include <pthread.h>

#include "rectangles.h"

#define BACKGROUND 40
#define FOREGROUND 36


#define NORTH    0
#define SOUTH    1
#define EAST     2
#define WEST     3
#define HERE     4

typedef struct {
	int rows;
	int columns;
	sc_rectangle* board;
	int map_rows;
	int map_columns;
	char **map;
	char player;
	int player_row;
	int player_column;
}Interface;

Interface * inter_create(int rows,int columns);

int set_player(Interface* i,char player,int row,int column);

void inter_delete(Interface*i);

int set_board(Interface* i,char **board,int row,int columns);

int draw_board(Interface *i, int clear) ;

int move (Interface *i,int direction);

int _read_key();

char **create_map(char *file,int *size); 


#endif
