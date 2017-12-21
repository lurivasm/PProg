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
void ck_count(void* max){
	time_t itime;
	itime=time(NULL);
	while(1){
		time_t instant;
		instant=time(NULL);
		if (instant-itime > *(int*)(max)){
			flag=1;
			pthread_exit (NULL);
			return;
		}
	}
}

static int Dr[5] = {-1, 1, 0, 0, 0};
static int Dc[5] = {0, 0, 1, -1, 0};
int mane(char** board, Interface* i){
	/*if (file==NULL) return 1;
	int sizeb[2],sizes[2],sizet[2];*/
	int mover;
	int nextcol,nextrow;
	int *place;
	/*char** board;
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

	set_player(i,'J',22,45);*/

	_term_init();
	flag = 0;
	while (flag == 0){
		draw_board(i,1);
		mover=_read_key();
		fflush(stdout);

		if (mover == 'q') {
      		tcsetattr(fileno(stdin), TCSANOW, &initial);	/*We now restore the settings we back-up'd
							  so that the termial behaves normally when
							  the program ends */
      		

      		return 3;
    	}
    	place=player_get_position(i);
    	nextrow=place[0]+Dr[-mover];
    	nextcol=place[1]+Dc[-mover];
    	free (place);
    	if (nextrow > 21 || nextcol >86) continue;

    	if (board[nextrow][nextcol] == '*'){
    			tcsetattr(fileno(stdin), TCSANOW, &initial);		      		
	      		return 0;

    	}
    	if (board[nextrow][nextcol] == 'M'){
    				tcsetattr(fileno(stdin), TCSANOW, &initial);     		

		      		return 1;

    	}

   		move(i,-mover);
		fflush(stdout);
	}
	/*free(score);
	free(text);
	free(board);*/

	tcsetattr(fileno(stdin), TCSANOW, &initial);	/*We now restore the settings we back-up'd
							  so that the termial behaves normally when
							  the program ends */
	return 0;
}

int play_mane(){
	Interface *i;
	int done=0,fail=0,res;
	int v[1];
	pthread_t pth;
	char map;
	int sizeb[2],sizes[2],sizet[2];
	int mover;
	int nextcol,nextrow;
	int *place;
	char** board;
	char** score;
	char** text;
	sc_rectangle* t;
	char p[280];

	i=inter_create(33,114,0,0,0,86,22,0);
	printf("\e[?25l");
	fflush(stdout);
	if (i == NULL) return -1;

	score = create_map("score",sizes);
	text = create_map("text",sizet);


	set_score(i,score,sizes[0],sizes[1]);
	draw_score(i,1);

	set_text(i,text,sizet[0],sizet[1]);
	draw_text(i,1);

	t = get_text(i);

	while (done<5 && fail<3){
		/*map=aleat_num(1,1);*/
		/*while(1){
			int quit = _read_key();
			if (quit == 'q')  return;
			if(quit == 32){
				break;
			}
		}*/
		
		board = create_map("1.txt",sizeb);
		
		set_board(i,board,sizeb[0],sizeb[1]);
		set_player(i,'J',21,45);
		draw_board(i,1);

		
		v[0]=100;
		pthread_create(&pth, NULL, ck_count, (void*)v);
		res = mane(board,i);
		if (res == 3){
			inter_delete(i);
			pthread_cancel(pth);
			return 1;
		}
		if (res == 1){
			pthread_cancel(pth);
			done++;
			sprintf(p,"%d %d",done,fail);
			win_write_line_at(t,4,4,p);
			continue;
		}
		else if (res == 0){
			pthread_cancel(pth);
			fail++;
			sprintf(p,"%d %d",done,fail);
			win_write_line_at(t,4,4,p);
			continue;
		}
		
		
	}

	int j;
	for(j = 0;j<sizeb[0];j++){
		free(board[j]);
	}
	for(j = 0;j<sizet[0];j++){
		free(text[j]);
	}
	for(j = 0;j<sizes[0];j++){
		free(score[j]);
	}

	free(board);
	free(text);
	free(score);
	inter_delete(i);
	if (done == 5) return 1;
	if (fail == 3) return -1;
	return -2;
}
