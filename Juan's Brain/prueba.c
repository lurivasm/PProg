#include <termios.h>
#include <pthread.h>
#include "juan.h"

struct termios initial;


int main(){
  char** score;
  char** text;
  char** board;
  int k;
  int sizeb[2],sizes[2],sizet[2];
  Interface* i;


  board = create_map("juan_board.txt",sizeb);
  score = create_map("score",sizes);
  text = create_map("text",sizet);

  i=inter_create(33,114,0,0,0,86,22,0);

  printf("\e[?25l");
	fflush(stdout);
  _term_init();


	set_board(i,board,sizeb[0],sizeb[1]);
	draw_board(i,1);
  set_score(i,score,sizes[0],sizes[1]);
  draw_score(i,1);

  set_text(i,text,sizet[0],sizet[1]);
  draw_text(i,1);

  main_juan(i);

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
  tcsetattr(fileno(stdin), TCSANOW, &initial);
  return 1;


}
