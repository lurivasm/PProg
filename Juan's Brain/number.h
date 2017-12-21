/*JUAN'S BRAIN*/
#ifndef NUMBER_H
#define NUMBER_H

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

#define ERR -1
#define WIN 10
#define LOOSE -10

/*Read from the keyboard the answer and compares the real number: returns ERR, 0 if they are equals and 1 if they're not*/
int number_compare(int number, int answer);

/*Generation of a random number: returns ERR or the random number*/
int number_rand(int min, int max);

/*The minigame: returns ERR, WIN or LOOSE*/
int Juan(Interface *i);

/*The final game with interface*/
void number_main(void);

#endif
