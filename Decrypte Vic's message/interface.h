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
	int r1;
	int c1;
	int rows;
	int columns;
	sc_rectangle* board;    /*Rectangulos en los que dividimos la pantalla*/
	int map_rows;
	int map_columns;
	char **map;
	char player;
	int player_row;
	int player_column;
}Interface;

/*Crea una interfaz de juego con x filas e y columnas*/
Interface * inter_create(int r1, int c1, int rows,int columns);

/*Posiciona al jugador en una interfaz con el caracter player en la fila row y columna column*/
int set_player(Interface* i,char player,int row,int column);

/*Elimina la interfaz*/
void inter_delete(Interface*i);

/*Establece la columnas y filas del mapa principal*/
int set_board(Interface* i,char **board,int row,int columns);

/**/
int draw_board(Interface *i, int clear);

/*Se mueve en la dirección establecida*/
int move (Interface *i,int direction);

/*Lee del teclado el movimiento*/
int _read_key();

/*Crea el mapa del fichero pasado. Size es un array de dos elementos (fila,columna)*/
char **create_map(char *file,int *size);


#endif
