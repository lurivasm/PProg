#ifndef HANGMAN_H
#define HANGMAN_H

#define ERR -1
#define OK (!(ERR))


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

typedef struct _hangman hangman;

hangman* hangman_ini(char* file1);

void hangman_destroy(hangman* hm);

void hangman_play(hangman* hm, FILE* out, FILE* in);

# endif
