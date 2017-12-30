#include "interface.h"
#include "mane.h"
#include <time.h>
#include <termios.h>
#include <pthread.h>
struct termios initial;

int flag = 0;

void _term_init() {
	struct termios new;/*a termios structure contains a set of attributes about
					  how the terminal scans and outputs data*/

	tcgetattr(fileno(stdin), &initial);    /*first we get the current settings of out
						 terminal (fileno returns the file descriptor
						 of stdin) and save them in initial. We'd better
						 restore them later on*/
	new = initial;	                      /*then we copy them into another one, as we aren't going
						to change ALL the values. We'll keep the rest the same */
	new.c_lflag &= ~ICANON;	              /*here we are setting up new. This line tells to stop the
						canonical mode (which means waiting for the user to press
						enter before sending)*/
	new.c_lflag &= ~ECHO;                 /*by deactivating echo, we tell the terminal NOT TO
						show the characters the user is pressing*/
	new.c_cc[VMIN] = 1;                  /*this states the minimum number of characters we have
					       to receive before sending is 1 (it means we won't wait
					       for the user to press 2,3... letters)*/
	new.c_cc[VTIME] = 0;	              /*I really have no clue what this does, it must be somewhere in the book tho*/
	new.c_lflag &= ~ISIG;                 /*here we discard signals: the program won't end even if we
						press Ctrl+C or we tell it to finish*/

	tcsetattr(fileno(stdin), TCSANOW, &new);  /*now we SET the attributes stored in new to the
						    terminal. TCSANOW tells the program not to wait
						    before making this change*/
}

static int Dr[5] = {-1, 1, 0, 0, 0};
static int Dc[5] = {0, 0, 1, -1, 0};
void moving (void *i){
    int mover;

    while (1){
        mover = _read_key();
        fflush(stdout);
        if (mover == 'q'){
          flag = 1;
          pthread_exit (NULL);
          return;
        }
        if (mover == -EAST || mover == -WEST) continue;
        move ((Interface*)i,-mover);
        fflush(stdout);
    }
}

int words(char *word,Interface *i,int place,int len){
    if (word == NULL || i == NULL) return -1;
    
}


int play_luis (Interface *i){
    moving (i);
    return 1;
}
