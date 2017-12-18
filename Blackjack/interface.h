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
	int rb;					/*initial row to write board*/
	int cb;					/*initial column to write board*/
	int rs;					/*initial row to write score*/
	int cs;					/*initial column to write score*/
	int rt;					/*initial row to write text*/
	int ct;					/*initial column to write text*/
	int rows;
	int columns;
	sc_rectangle* board;
	sc_rectangle* score;
	sc_rectangle* text;
	int mapb_rows;
	int mapb_columns;
	int maps_rows;
	int maps_columns;
	int mapt_rows;
	int mapt_columns;
	char **mapb;        /*board map*/
	char **maps;        /*score map*/
	char **mapt;        /*text map*/
	char player;
	int player_row;
	int player_column;
}Interface;

void _term_init();


/*i=inter_create(33,114,0,0,0,86,22,0);*/
Interface * inter_create(int rows,int columns,int rb,int cb,int rs,int cs,int rt,int ct);

int set_player(Interface* i,char player,int row,int column);

void inter_delete(Interface*i);

int set_board(Interface* i,char **board,int row,int columns);

int set_score(Interface* i,char **score,int row,int columns);

int set_text(Interface* i,char **text,int row,int columns);

int draw_board(Interface *i, int clear) ;

int draw_score(Interface* i, int clear);

int draw_text(Interface* i, int clear);

int move (Interface *i,int direction);

int _read_key();

char **create_map(char *file,int *size);

sc_rectangle* get_board(Interface *i);

sc_rectangle* get_score(Interface *i);

sc_rectangle* get_text(Interface *i);

int* player_get_position(Interface *i);

#endif
