
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
#include "message.h"


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
	int quit, game, key;
	int j=0,k;
	char** board;
	char** score;
	char** text;
	int sizeb[2],sizes[2],sizet[2],mode;


 /*We create the maps for the board,score and text and set them on the interface*/
	board = create_map("vic.txt",sizeb);
	score = create_map("score",sizes);
	text = create_map("text",sizet);

	i = inter_create(33,114,0,0,0,86,22,0);

	set_board(i, board, sizeb[0], sizeb[1]);
	draw_board(i, 1);

	set_score(i, score, sizes[0], sizes[1]);
	draw_score(i,1);

	set_text(i, text, sizet[0], sizet[1]);
	draw_text(i,1);

	_term_init();


	sc_rectangle* t;
 	t = get_text(i);
 	if(!t) return;


	win_write_line_at(t,4,4,"Press the space bar to continue");



	printf("\e[?25l");
  fflush(stdout);

	while(1){
		quit = _read_key();
		/*pressing q it exits*/
		if (quit == 'q') {
			inter_delete(i);
	    tcsetattr(fileno(stdin), TCSANOW, &initial);	/*We now restore the settings we back-up'd
								  so that the termial behaves normally when
								  the program ends */
	    return;
	  }
		/*if you press the space bar,you move foward*/
		if(quit == 32){
			int k;
			for(k = 0; k < sizeb[0]; k++){
				free(board[k]);
			}
			free(board);
			break;
		}
	}
/*we create the new map,and draw it in board*/
	play: board = create_map("vic_board.txt",sizeb);
	set_board(i, board, sizeb[0], sizeb[1]);
	draw_board(i, 1);
	draw_text(i, 1);

	/*We call the game*/
 game = Vic(i);

	if(game == LOOSE){
		for(k = 0; k < sizeb[0]; k++){
			free(board[k]);
		}
		free(board);

		board = create_map("looser.txt",sizeb);
		set_board(i, board, sizeb[0], sizeb[1]);
		draw_board(i, 1);
		win_write_line_at(t,4,4,"Do you want to play again? [y/n]");

		while(1){
			key = _read_key();
			if(key != 'y' && key != 'n') continue;
			if(key == 'y') goto play;
			else {break;}

		}
	}

	for(k = 0; k < sizeb[0]; k++){
		free(board[k]);
	}
	free(board);

	board = create_map("winner.txt",sizeb);
	set_board(i, board, sizeb[0], sizeb[1]);
	draw_board(i, 1);
	win_write_line_at(t,4,4,"Thanks for playing!");


	tcsetattr(fileno(stdin), TCSANOW, &initial);
	for(k = 0; k < sizeb[0]; k++){
		free(board[k]);
	}
	for(k = 0;k < sizet[0]; k++){
		free(text[k]);
	}
	for(k = 0; k < sizes[0]; k++){
		free(score[k]);
	}

	free(board);
	free(text);
	free(score);

	return;
}
