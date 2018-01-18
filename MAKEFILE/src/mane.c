#include "interface.h"
#include "mane.h"
#include <time.h>
#include <termios.h>
#include <pthread.h>


int flag = 0;

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

	int mover;
	int nextcol,nextrow;
	int *place;


	flag = 0;
	while (flag == 0){
		draw_board(i,1);
		mover=_read_key();
		fflush(stdout);

		if (mover == 'q') {
      		return 3;
    	}
    	place=player_get_position(i);
    	nextrow=place[0]+Dr[-mover];
    	nextcol=place[1]+Dc[-mover];
    	free (place);
    	if (nextrow > 21 || nextcol >86) continue;

    	if (board[nextrow][nextcol] == '*'){
     		return 0;

    	}
    	if (board[nextrow][nextcol] == 'M'){


		      		return 1;

    	}

   		move(i,-mover);
		fflush(stdout);
	}


	return 0;
}

int play_mane(Interface *i){
	int done = 0,fail = 0,res,quit;
	int v[1];
	pthread_t pth;
	char map[10];
	int wololo;
	int sizeb[2],sizes[2],sizet[2];
	int mover;
	int nextcol,nextrow;
	int *place;
	char** board;
	sc_rectangle* t, *s;
	char p[280];

	srand (time(NULL));
	printf("\e[?25l");
	fflush(stdout);
	if (i == NULL) return -1;

	board = create_map("beginin.txt",sizeb);



	draw_score(i,1);


	draw_text(i,1);

	set_board(i,board,sizeb[0],sizeb[1]);
	draw_board(i,1);

	t = get_text(i);

	s = get_score(i);



	win_write_line_at(t,4,4,"Press the space bar to continue");

	win_write_line_at (s,3,6,"The rules are simple:");

	win_write_line_at(s,5,6,"You have to reach the");

	win_write_line_at(s,6,6,"M before the time");

	win_write_line_at(s,7,6,"expires, but you");

	win_write_line_at(s,8,6,"won't know it");

	win_write_line_at(s,9,6,"Good luck!");

	while(1){
	quit = _read_key();
	/*pressing q it exits*/
	if (quit == 'q')  return 1;
	/*if you press the space bar,you move foward*/
	if(quit == 32){
		int k;
		for(k = 0;k<sizeb[0];k++){
			free(board[k]);
		}
		free(board);
		break;
	}
	}


	draw_text(i,1);
	draw_score(i,1);

	win_write_line_at(s,4,6,"Score:");

	win_write_line_at(s,6,6,"Win: 0");

	win_write_line_at(s,8,6,"Fail: 0");

	while (done<5 && fail<3){

		wololo=(rand()%3) + 1;
		draw_text(i,1);

		sprintf(map,"%d.txt",wololo);

		board = create_map(map,sizeb);

		set_board(i,board,sizeb[0],sizeb[1]);
		set_player(i,'J',21,45);
		draw_board(i,1);


		v[0]=100;
		pthread_create(&pth, NULL, ck_count, (void*)v);
		res = mane(board,i);
		if (res == 3){
			pthread_cancel(pth);
			return 1;
		}
		if (res == 1){
			pthread_cancel(pth);
			done++;
			sprintf(p,"%d",done);
			win_write_line_at(s,6,11,p);
		}
		else if (res == 0){
			pthread_cancel(pth);
			fail++;
			sprintf(p,"%d",fail);
			win_write_line_at(s,8,12,p);
		}
		win_write_line_at(t,4,4,"Press the space bar to begin the round");

		while(1){
		quit = _read_key();
		/*pressing q it exits*/
		if (quit == 'q')  return 	1;
		/*if you press the space bar,you move foward*/
		if(quit == 32){
			int k;
			for(k = 0;k<sizeb[0];k++){
				free(board[k]);
			}
			free(board);
			break;
			}
		}

	}

	
	if (done == 5) return 1;
	if (fail == 3) return 0;
	return -2;
}
