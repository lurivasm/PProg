/*THE FINAL GAME*/
#ifndef JAVITI_H
#define JAVITI_H

#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <time.h>
#include <unistd.h>


#include <termios.h>
#include <pthread.h>
#include "interface.h"
#include "world.h"

#define ERR -1
#define WIN 1
#define LOOSE 0


/*The minigame: returns ERR, WIN or LOOSE*/
int Javiti(Interface *i,World *w);

/*The final game with interface*/
int  main_javiti(Interface *i,World *w);

#endif
