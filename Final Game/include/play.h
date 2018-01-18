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
/*  Made by: Daniel Santo-Tomás                 */
/************************************************/

#ifndef PLAY_H
#define PLAY_H


#include <termios.h>
#include <pthread.h>
#include "world.h"
#include "blackjack.h"
#include "dani.h"
#include "mane.h"
#include "luis.h"
#include "lucia.h"
#include "juan.h"
#include "hangman.h"
#include "javiti.h"


int play(World *w ,Interface *i);


#endif
