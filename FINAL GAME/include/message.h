/*DECRYPT VIC'S MESSAGE*/
#ifndef MESSAGE_H
#define MESSAGE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "interface.h"

#define ERR -1
#define WIN 10
#define LOOSE -10

typedef struct _message Message;
typedef struct _game Game;


/*Last game*/
int main_vic(Interface *in);

#endif
