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
#include "blackjack.h"

struct termios initial;




void main(){
  Interface* i;
  int m;
	int *p;
  int j,game,flag = 1;
  char** board;
  char** score;
  char** text;
  int sizeb[2],sizes[2],sizet[2];
  int played[12];
  for(j = 0;j < 12 ; j++) played[j] = 0;
  srand(time(NULL));


	p = (int*)malloc(sizeof(int)*2);


  /*We create the maps for the board,score and text and set them on the interface*/
  board = create_map("mapa_metro.txt",sizeb);
  score = create_map("score",sizes);
  text = create_map("text",sizet);

  i=inter_create(33,114,0,0,0,86,22,0);

  set_player(i,'J',12,35); /* 12 35 */
	printf("\e[?25l");
	fflush(stdout);
	 _term_init();

	  set_board(i,board,sizeb[0],sizeb[1]);
	  draw_board(i,1);

	  set_score(i,score,sizes[0],sizes[1]);
	  draw_score(i,1);

	  set_text(i,text,sizet[0],sizet[1]);
	  draw_text(i,1);

	while(1){
		m = _read_key();
		/*pressing q it exits*/
		if (m == 'q')	break;



	  move(i,-m);
		p = player_get_position(i);
		if(p[1] == 83 && (p[0] == 3 || p[0] == 4 || p[0] == 5 )){
			set_player(i,' ',0,0);
			draw_board(i,1);
      game = rand()%1;
      while(flag){
        if(played[game] == 1){
          game = rand()%2;
        }
        flag = 0;
      }
      switch (game) {
        case(0):
          main_Blackjack(i);
          break;
        case(1):
          break;
      }
      played[game] = 1;
			break;
		}
	}



	set_board(i,board,sizeb[0],sizeb[1]);
	set_player(i,'J',p[0],p[1]);
	draw_board(i,1);
	draw_text(i,1);
	draw_score(i,1);

	while(1){
		m = _read_key();
		/*pressing q it exits*/
		if (m == 'q')	break;
		move(i,-m);
	}


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
	tcsetattr(fileno(stdin), TCSANOW, &initial);	/*We now restore the settings we back-up'd
							so that the termial behaves normally when
							the program ends*/
}
