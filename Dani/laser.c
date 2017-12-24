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

int tim = 100000;

void laser(void *i){
  int cont = 0,r,c;
  sc_rectangle *b,*t;
  b = get_board(i);
  t = get_text(i);

  while(cont !=5){
    r = 20;
    c = rand()%80+ 3;
    win_write_char_at(b,20,c,'o');

    while(r != 1){

      win_write_char_at(b,r,c,' ');
      win_write_char_at(b,r-1,c,'o');
      win_write_char_at(b,r,c,' ');
      win_write_char_at(b,r,c,' ');
      win_write_char_at(b,r,c,' ');
      r--;

      usleep(tim);
    }
    win_write_char_at(b,r,c,' ');
    cont++;

  }
  pthread_exit (NULL);
  return;
}


void main(){
  Interface* i;
	int *p;
  int j,r,c,cont = 0,m;
  char** board;
  char** score;
  char** text;
  pthread_t pth1,pth2,pth3;
  int sizeb[2],sizes[2],sizet[2];
  int played[12];
  for(j = 0;j < 12 ; j++) played[j] = 0;
  srand(time(NULL));


	p = (int*)malloc(sizeof(int)*2);


  /*We create the maps for the board,score and text and set them on the interface*/
  board = create_map("tr",sizeb);
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

  tim = 99980;
  pthread_create(&pth1, NULL, laser,(void*)(i));
  usleep(1000000);
  pthread_create(&pth2, NULL, laser,(void*)(i));
  usleep(1000000);
  pthread_create(&pth3, NULL, laser,(void*)(i));
  while(1){
    m = _read_key();
    if(m == 'q') break;
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
