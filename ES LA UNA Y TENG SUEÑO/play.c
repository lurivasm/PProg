#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <time.h>
#include <unistd.h>


#include <termios.h>
#include <pthread.h>
#include "world.h"
#include "blackjack.h"
#include "dani.h"

struct termios initial;




void main(){
  Interface* i;
  World *w;
  int m;
	int *p;
  int j,game,flag = 1,res;
  sc_rectangle *t,*b,*s;
  Player *pl;
  char** board;
  char** score;
  char** text;
  int sizeb[2],sizes[2],sizet[2];
  char* name = (char*)malloc(sizeof(char)*30);
  char query[200]; /*EDAT reference haha XD lol*/
  srand(time(NULL));


	p = (int*)malloc(sizeof(int)*2);


  /*We create the maps for the board,score and text and set them on the interface*/
  board = create_map("mapa_metro.txt",sizeb);
  score = create_map("score",sizes);
  text = create_map("text",sizet);

  i=inter_create(33,114,0,0,0,86,22,0);
  w = create_world();



  set_player(i,'J',11,35); /* 12 35 */
	printf("\e[?25l");
	fflush(stdout);
	 _term_init();

	  set_board(i,board,sizeb[0],sizeb[1]);
	  draw_board(i,1);

	  set_score(i,score,sizes[0],sizes[1]);
	  draw_score(i,1);

	  set_text(i,text,sizet[0],sizet[1]);
	  draw_text(i,1);

    b = get_board(i);
    t = get_text(i);
    s = get_score(i);
    pl = get_player(w);

    sprintf(query,"%d (%%)",get_alcohol(pl));
    win_write_line_at(s,4,4,query);

	while(1){
    flag = 1;
    name = get_station(w);
    win_write_line_at(b,2,33,name);
    if(strcmp(name,"JOAQUÍN VILUMBRALES") == 0) break;
    sprintf(query,"Oh,you fell asleep and you woke up in %s",name);
    win_write_line_at(t,4,4,query);
    usleep(3000000);
    while(1){
		    m = _read_key();
		    /*pressing q it exits*/
		    if (m == 'q')	return;
        if (m == 'f') break;
	      move(i,-m);
		    p = player_get_position(i);
        if(p[1] == 83 && (p[0] == 3 || p[0] == 4 || p[0] == 5 ))break;
    }
    if(minigames(w) == 2) break;
			set_player(i,' ',0,0);
			draw_board(i,1);
      game = rand()%2;

      while(flag){

        if(read_played(w,game) == 1){
          game = rand()%2;
          continue;
        }
        flag = 0;
      }
      switch (game) {
        case 0:
          res = main_Blackjack(i);
          break;
        case 1:
          res = main_dani(i);
          break;
        /*case 2:
          res = main_lucia(i);
          break;*/
      }
      write_played(w,game);


      switch (res) {
        case 0 :
          if(game == 2){
            modify_alcohol(pl,30);
            break;
          }
          modify_alcohol(pl,20);
          break;
        case 1 :
          if(game == 2){
            modify_alcohol(pl,10);
            break;
          }
          modify_alcohol(pl,-10);
          break;
        case 2 :
          modify_alcohol(pl,20);
          break;
        case 3 :
          modify_alcohol(pl,30);
          break;
        case 4 :
          modify_alcohol(pl,-20);
          break;
      }

      if(get_alcohol(pl) == 100) return -1;
      set_player(i,'J',4,83);
      set_board(i,board,sizeb[0],sizeb[1]);
      draw_board(i,1);
      draw_text(i,1);
      draw_score(i,1);

      win_write_line_at(b,2,33,name);
      sprintf(query,"%d (%%)",get_alcohol(pl));
      win_write_line_at(s,4,4,query);
      usleep(1000000);
      win_write_line_at(s,6,4,"Get to the train");
      while(1){
        m = _read_key();
        if(m == 'q') return;
        if(m == 'f') break;
        move(i,-m);
        p = player_get_position(i);
        if(p[0] == 11) break;
      }
      usleep(2000000);
      board = create_map("tr",sizeb);
      set_board(i,board,sizeb[0],sizeb[1]);
      set_player(i," ",0,0);
      draw_board(i,1);
      usleep(5000000);
      board = create_map("mapa_metro.txt",sizeb);
      set_board(i,board,sizeb[0],sizeb[1]);
      set_player(i,'J',p[0],p[1]);
      draw_board(i,1);
      draw_score(i,1);

	}

  win_write_line_at(t,4,4,"Oh,you got home!");
  usleep(3000000);



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
