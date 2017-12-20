/*DECRYPT VIC'S MESSAGE*/
#ifndef MESSAGE_H
#define MESSAGE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interface.h"

#define ERR -1
#define WIN 10
#define LOOSE -10

typedef struct _message Message;
typedef struct _game Game;

/*Last game*/
int Vic(Interface *i);

/*Initialization of a message*/
Message *message_ini();

/*Destruction of messages*/
void message_destroy(Message *m);

/*Destruction of an array of messages*/
void message_array_destroy(Message **m);

/*Read from the file and set the messages and their numbers*/
int message_set(Message **m, char *f);

/*Read from the keyboard the answer and compares the real message*/
int message_compare(Message *m, char* answer);

/*Inicialization of a game struct with the array of sentences*/
Game *game_ini(char *file);

/*The minigame*/
int message_game(char *file);

#endif
