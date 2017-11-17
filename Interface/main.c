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

struct termios initial;

void _term_init() {
	struct termios new;	          /*a termios structure contains a set of attributes about
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

void main(){
	Interface* i;
	FILE *f;
	int mover;
	int j=0;
	char** map;
	f=fopen("prueba","r");
	if (f==NULL){
		printf("falla lectura\n");
		return;
	}
	char buf[1000];
	int rows = atoi(fgets(buf, 1000, f));
	int cols = atoi(strchr(buf, ' ')+1);

	map=(char**)malloc(sizeof(char*)*rows);
	for(int r=0;r<rows;r++){
		map[r]=(char*)malloc(cols+1);
		fgets(buf, 1000, f);
		int k=0;
		if (buf[strlen(buf)] == '\n')
			buf[strlen(buf)] = 0;
		for (;k<strlen(buf); k++)
			map[r][k] = buf[k];
		for (;k<cols; k++)
			map[r][k] = ' ';
		map[r][k] = 0;
	}

	fclose(f);

	i=inter_create(rows,cols);
	set_player(i,'c',3,33);
	set_board(i,map,rows,cols);
	draw_board(i,1);
	_term_init();
	while (1){
		mover=_read_key();
		fflush(stdout);

		if (mover == 'q') {
      tcsetattr(fileno(stdin), TCSANOW, &initial);	/*We now restore the settings we back-up'd
							  so that the termial behaves normally when
							  the program ends */
      return;
    }
		move(i,-mover);
		fflush(stdout);
	}
	inter_delete(i);
	return;
}
