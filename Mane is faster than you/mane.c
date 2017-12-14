#include "interface.h"
#include "mane.h"
#include <time.h>

struct termios initial;

int flag=0;

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
			flag=1;
			return;
		}
	}
}

int move_mane(Interface *i,int direction){
	if (i==NULL||direction>4||direction<0) return -3;
	int r,c;
	r=i->player_row+Dr[direction];
	c=i->player_column+Dc[direction];
	if(r<0||c<0||r>=i->rows||c>=i->columns) return -2;
	if (i->mapb[r][c]!=' ') {
		return -1;
	}
  if (i->mapb[r][c] == '*'){
		return -2;
	}
	if (i->mapb[r][c] == 'M'){
		return 1;
	}
	win_write_char_at(i->board,i->player_row,i->player_column,' ');
	i->player_column=c;
	i->player_row=r;
	win_write_char_at(i->board,i->player_row,i->player_column,i->player);
	return r<<8 +c;
}
int mane(char* file; Interface* i){
	if (file==NULL) return 1;
	int sizeb[2],sizes[2],sizet[2];
	int mover;
	char** board;
	char** score;
	char** text;
	board = create_map(file,sizeb);
	score = create_map("score",sizes);
	text = create_map("text",sizet);
	set_board(i,board,sizeb[0],sizeb[1]);
	draw_board(i,1);

	set_score(i,score,sizes[0],sizes[1]);
	draw_score(i,1);

	set_text(i,text,sizet[0],sizet[1]);
	draw_text(i,1);

	set_player(i,'J',23,44);

	free(board);
	free(score);
	free(text);

	_term_init();
	flag=0;
	while (flag == 0){
		mover=_read_key();
		fflush(stdout);

		if (mover == '1') {
      		tcsetattr(fileno(stdin), TCSANOW, &initial);	/*We now restore the settings we back-up'd
							  so that the termial behaves normally when
							  the program ends */
      		return 3;
    	}
    mover=move_mane(maze,-mover);
		if (mover == '-2') {
						tcsetattr(fileno(stdin), TCSANOW, &initial);	/*We now restore the settings we back-up'd
								  so that the termial behaves normally when
								  the program ends */
	      		return 0;
	    }
		if (mover == '1') {
							tcsetattr(fileno(stdin), TCSANOW, &initial);	/*We now restore the settings we back-up'd
									  so that the termial behaves normally when
									  the program ends */
		      		return 1;
		    }

		fflush(stdout);
	}


	tcsetattr(fileno(stdin), TCSANOW, &initial);	/*We now restore the settings we back-up'd
							  so that the termial behaves normally when
							  the program ends */
      		return 0;
}

int play_mane(){
	Interface *i;
	int done=0,fail=0,res;
	pthread_t pth;
	char map;
	i=inter_create(33,114,0,0,0,86,22,0);
	if (i==NULL) return -1;
	while (done<6 || fail<3){
		pthread_create(&pth, NULL, ck_count, 20);
		res = mane(map,i);
		if (res == 3){
			return 1;
		}
		if (res == 1){
			done ++;
		}
		else if (res == 0){
			fail++;
		}
	}
}
