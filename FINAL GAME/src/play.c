#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <time.h>
#include <unistd.h>


#include "play.h"


struct termios initial;



int play(World *w,Interface *i){
  int m,sav;
	int *p;
  int j,game,flag = 1,res;
  sc_rectangle *t,*b,*s;
  Player *pl;
  char** board;
  int sizeb[2];
  char* name = (char*)malloc(sizeof(char)*30);
  char query[200]; /*EDAT reference haha XD lol*/
  srand(time(NULL));


	p = (int*)malloc(sizeof(int)*2);


  /*We create the maps for the board,score and text and set them on the interface*/
  board = create_map("mapa_metro.txt",sizeb);



  _term_init();
  set_player(i,'J',11,35); /* 12 35 */
	printf("\e[?25l");
	fflush(stdout);


	  set_board(i,board,sizeb[0],sizeb[1]);
	  draw_board(i,1);

	  draw_score(i,1);
	  draw_text(i,1);

    b = get_board(i);
    t = get_text(i);
    s = get_score(i);

    pl = get_player(w);
    sprintf(query,"Life : %d (%%)",get_alcohol(pl));
    win_write_line_at(s,4,4,query);

	while(1){
    flag = 1;
    name = get_station(w);
    win_write_line_at(b,2,33,name);
    if(strcmp(name,"JOAQUÍN VILUMBRALES") == 0) break;
    sprintf(query,"Oh,you fell asleep and you woke up in %s",name);
    win_write_line_at(t,4,4,query);
    sprintf(query,"Life : %d (%%)",get_alcohol(pl));
    win_write_line_at(s,4,4,query);
    usleep(3000000);

    draw_text(i,1);
    while(1){
      win_write_line_at(t,4,4,"Do you want to save your game?[y/n]: ");
      sav = _read_key();
      if(sav != 'y' && sav != 'n') continue;
      if(sav == 'y'){
        tcsetattr(fileno(stdin), TCSANOW, &initial);
        slot : win_write_line_at(t,5,4,"In which slot you want to save the game?[1/2/3]:");
        fscanf(stdin,"%d",&sav);
        if(sav != 1 && sav != 2 && sav != 3) goto slot;
        _term_init();
        save(w,sav);
      }
      draw_text(i,1);
      break;
    }

    while(1){
		    m = _read_key();
		    /*pressing q it exits*/
		    if (m == 'q'){
            tcsetattr(fileno(stdin), TCSANOW, &initial);	/*We now restore the settings we back-up'd
          							so that the termial behaves normally when
          							the program ends*/
          	return;
          }
        if(m == 'f') goto final;
	      move(i,-m);
		    p = player_get_position(i);
        if(p[1] == 83 && (p[0] == 3 || p[0] == 4 || p[0] == 5 ))break;
    }

			set_player(i,' ',0,0);
			draw_board(i,1);
      game = rand()%6;

      while(flag){

        if(read_played(w,game) == 1){
          game = rand()%6;
          continue;
        }
        flag = 0;
      }

      switch (game) {
        case 0:
          res = main_Blackjack(i,w);
          break;
        case 1:
          res = main_dani(i);
          break;
        case 2:
          res = main_lucia(i);
          break;
        case 3:
          draw_text(i,1);
          draw_score(i,1);
          res = main_juan(i);
          break;
        case 4:
          res = play_luis(i);
          break;
        case 5:
          res = play_mane(i);
          break;
        case 6:
          res = main_hangman(i);
          break;
        case 7:
          res = main_vic(i);
          break;
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

      if(get_alcohol(pl) >=100){

         return -1;
       }
      set_player(i,'J',4,83);
      set_board(i,board,sizeb[0],sizeb[1]);
      draw_board(i,1);
      draw_text(i,1);
      draw_score(i,1);

      win_write_line_at(b,2,33,name);
      sprintf(query,"Life : %d (%%)",get_alcohol(pl));
      win_write_line_at(s,4,4,query);
      usleep(1000000);
      win_write_line_at(s,6,4,"Get to the train");
      while(1){
        m = _read_key();
        if(m == 'q'){
          tcsetattr(fileno(stdin), TCSANOW, &initial);	/*We now restore the settings we back-up'd
        							so that the termial behaves normally when
        							the program ends*/
          return;
        }

        move(i,-m);
        p = player_get_position(i);
        if(p[0] == 11) break;
      }
      usleep(2000000);
      board = create_map("tr",sizeb);
      set_board(i,board,sizeb[0],sizeb[1]);
      set_player(i,' ',0,0);
      draw_board(i,1);
      draw_score(i,1);
      usleep(5000000);
      board = create_map("mapa_metro.txt",sizeb);
      set_board(i,board,sizeb[0],sizeb[1]);
      set_player(i,'J',p[0],p[1]);
      draw_board(i,1);
      draw_score(i,1);

	}

final:  win_write_line_at(t,4,4,"Oh,you got home!");
  usleep(3000000);

  while(1){
      m = _read_key();
      /*pressing q it exits*/
      if (m == 'q'){
            tcsetattr(fileno(stdin), TCSANOW, &initial);	/*We now restore the settings we back-up'd
          							so that the termial behaves normally when
          							the program ends*/
            return;
        }
      move(i,-m);
      p = player_get_position(i);
      if(p[1] == 83 && (p[0] == 3 || p[0] == 4 || p[0] == 5 ))break;
  }

    res = main_javiti(i,w);




  for(j = 0;j<sizeb[0];j++){
		free(board[j]);
	}


	free(board);


  tcsetattr(fileno(stdin), TCSANOW, &initial);	/*We now restore the settings we back-up'd
							so that the termial behaves normally when
							the program ends*/
   return res;
}
