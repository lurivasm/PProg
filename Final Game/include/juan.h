/************************************************/
/*              PPROG VIDEOGAME                 */
/*         DREAM OF A JAVITI'S NIGHT            */
/*                                              */
/*  Members of the group:                       */
/*           - Javier Martínez                  */
/*           - Lucía Rivas                      */
/*           - Daniel Santo-Tomás               */
/*           - Juan Velasco                     */
/*                                              */
/*  Made by: Lucía Rivas                        */
/************************************************/
/*JUAN'S BRAIN*/
#ifndef JUAN_H
#define JUAN_H

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
#define WIN 1
#define LOOSE 0


/*Generation of a random number: returns ERR or the random number*/
int number_rand(int min, int max);

/*The minigame: returns ERR, WIN or LOOSE*/
int Juan(Interface *i);

/*The final game with interface*/
int main_juan(Interface *i);

#endif
