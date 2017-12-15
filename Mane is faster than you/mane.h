#ifndef MANE_H
#define MANE_H
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <time.h>
#include <unistd.h>
#include "permutaciones.h"


#include <termios.h>
#include <pthread.h>

#include "interface.h"
int mane(char* file, Interface* i);
int play_mane();
#endif
