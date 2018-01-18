#ifndef PLAY_H
#define PLAY_H


#include <termios.h>
#include <pthread.h>
#include "world.h"
#include "blackjack.h"
#include "dani.h"
#include "message.h"
#include "mane.h"
#include "luis.h"
#include "lucia.h"
#include "juan.h"
#include "hangman.h"

int play(World *w ,Interface *i);


#endif
