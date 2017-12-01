#include "interface.h"
#include "mane.h"
#include <time.h>

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
void ck_count(int max){
	time_t itime;
	itime=time(NULL);
	while(1){
		time_t instant;
		instant=time(NULL);
		if (instant-itime>max){
			return;
		}
	}
}
int mane(char* file){
	if (file==NULL) return 1;
	Interface *maze;
	int size [2];
	int flag=0,mover;
	char **map;
	map=create_map(file,size);
	maze=inter_create(size[0],size[1]);
	set_player(maze,'J',23,22);
	set_board(maze,map,size[0],size[1]);
	draw_board(maze,1);
	_term_init();
	while (flag!=-2){
		mover=_read_key();
		fflush(stdout);

		if (mover == 'q') {
      		tcsetattr(fileno(stdin), TCSANOW, &initial);	/*We now restore the settings we back-up'd
							  so that the termial behaves normally when
							  the program ends */
      		return 0;
    	}
    	flag=move(maze,-mover);
    	
		fflush(stdout);
	}
	map=create_map("lose.txt",size);
	set_board(maze,map,size[0],size[1]);
	draw_board(maze,1);

	tcsetattr(fileno(stdin), TCSANOW, &initial);	/*We now restore the settings we back-up'd
							  so that the termial behaves normally when
							  the program ends */
      		return 1;
}