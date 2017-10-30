/*DECRYPT VIC'S MESSAGE*/
#ifndef MESSAGE_H
#define MESSAGE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ERR -1

typedef struct _message Message;
typedef struct _game Game;

/*Initialization of a message*/
Message *message_ini();

/*Destruction of messages*/
void message_destroy(Message *m);

/*Read from the file and set the messages and their numbers*/
int message_set(Message **m, char *f);

/*Read from the keyboard the answer and compares the real message*/
int message_compare(Message *m, char* answer);

/*The minigame*/
int message_game();

#endif