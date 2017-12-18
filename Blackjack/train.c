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




void main(){
  Interface* i;
  FILE *f;
  int m;
  int j=0,k;
  char** board;
  char** score;
  char** text;
  int sizeb[2],sizes[2],sizet[2],mode;


  /*We create the maps for the board,score and text and set them on the interface*/
  board = create_map("tr",sizeb);
  score = create_map("score",sizes);
  text = create_map("text",sizet);

  i=inter_create(33,114,0,0,0,86,22,0);

  set_player(i,'D',5,6);
	printf("\e[?25l");

  set_board(i,board,sizeb[0],sizeb[1]);
  draw_board(i,1);

  set_score(i,score,sizes[0],sizes[1]);
  draw_score(i,1);

  set_text(i,text,sizet[0],sizet[1]);
  draw_text(i,1);

  set_player(i,'D',5,6);

  _term_init();

  while(1){
	m = _read_key();
	/*pressing q it exits*/
	if (m == 'q') {
		inter_delete(i);
    tcsetattr(fileno(stdin), TCSANOW, &initial);	/*We now restore the settings we back-up'd
							  so that the termial behaves normally when
							  the program ends */
    return;
  }
  move(i,-m);
	}

  tcsetattr(fileno(stdin), TCSANOW, &initial);
  for(k = 0;k<sizeb[0];k++){
		free(board[k]);
	}
	for(k = 0;k<sizet[0];k++){
		free(text[k]);
	}
	for(k = 0;k<sizes[0];k++){
		free(score[k]);
	}

	free(board);
	free(text);
	free(score);
	tcsetattr(fileno(stdin), TCSANOW, &initial);	/*We now restore the settings we back-up'd
							so that the termial behaves normally when
							the program ends*/
}
