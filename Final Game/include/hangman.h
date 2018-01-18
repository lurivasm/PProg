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
/*  Made by: Javier Martínez                    */
/************************************************/
#ifndef HANGMAN_H
#define HANGMAN_H

#define ERR -1
#define OK (!(ERR))


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "interface.h"

typedef struct _hangman hangman;

int main_hangman(Interface *i);

hangman* hangman_ini(char* file1);

void hangman_destroy(hangman* hm);

int hangman_play(hangman* hm, FILE* out, FILE* in, Interface* ini);

# endif
