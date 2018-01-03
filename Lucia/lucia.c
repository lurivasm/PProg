#include "lucia.h"



void main_lucia(Interface *i){

  int quit,res;
	char** board;
	int sizeb[2];
  int *p = (int*)malloc(sizeof(int)*2);


 /*We create the maps for the board,score and text and set them on the interface*/
	board = create_map("olympics",sizeb);


	set_board(i,board,sizeb[0],sizeb[1]);

	draw_board(i,1);

	draw_score(i,1);

	draw_text(i,1);


	sc_rectangle *t,*s;
 	t = get_text(i);
  s = get_score(i);
 	if(!t || !s) return;

	win_write_line_at(t,4,4,"Press the space bar to continue");




	while(1){
	quit = _read_key();
	/*pressing q it exits*/
	if (quit == 'q')   return;
	/*if you press the space bar,you move foward*/
	if(quit == 32) break;
	}

  draw_text(i,1);

  board = create_map("room",sizeb);
  set_board(i,board,sizeb[0],sizeb[1]);
  set_player(i,'J',6,40);
  draw_board(i,1);

  win_write_line_at(t,4,4,"A: So,let's begin with the 2017 alcoholympics final!");
  usleep(4000000);
  win_write_line_at(t,5,4,"A: Our two finalists are Javiti and Lucia");
  usleep(3000000);
  win_write_line_at(t,6,4,"A: So please both of you go to the beer table to start with the first task");
  usleep(4000000);
  draw_text(i,1);
  win_write_line_at(t,4,4,"L: Aim goin tu wuin,aim an expert in drinkin");
  usleep(2000000);
  win_write_line_at(s,4,4,"Get to the beer table");

while(1){
  quit = _read_key();
  if(quit == 'q') return;
  move(i,-quit);
  p = player_get_position(i);
  if(p[0] == 7 && p[1] == 16){
    res = beer(i);
    break;
  }
}




}


void drink_beer(sc_rectangle *b, int r,int c){
  win_write_line_at(b,r,c,"|                |");
  return;
}



int lose ;

void lucia_beer(void *b){
  int r = 7;
  lose = 0;
  while(r < 18 ){
    usleep(3000000);
    drink_beer(b,r,60);
    r++;
  }

   lose = 1;
}

int beer(Interface *i){

  char** board;
  int sizeb[2];
  int drink,cont = 0,r = 7,d = 15;
  pthread_t pth;

  board = create_map("beer",sizeb);
  set_player(i,' ',0,0);
  set_board(i,board,sizeb[0],sizeb[1]);

  draw_board(i,1);
  draw_score(i,1);
  draw_text(i,1);

  sc_rectangle *t,*s,*b;
  t = get_text(i);
  s = get_score(i);
  b = get_board(i);

  win_write_line_at(t,4,4,"A: Okay,in this first task ,the one who finishes the beer first is the winner");
  usleep(3000000);
  win_write_line_at(s,4,4,"Press the space bar ");
  win_write_line_at(s,5,4,"repeatedly to drink");
  usleep(5000000);
  win_write_line_at(t,5,4,"So this begins in 3");
  usleep(1000000);
  win_write_line_at(t,5,25,"2");
  usleep(1000000);
  win_write_line_at(t,5,27,"1");
  usleep(3000000);
  win_write_line_at(t,5,29,"GO!");

  pthread_create(&pth, NULL, lucia_beer,(void*)(b));
  char p[30];
  while(r < 18 && lose == 0){
    drink = _read_key();
    if(drink == 'q') return 1;
    if(drink == 32) cont++;
    if(cont == d ){
      drink_beer(b,r,18);
      r++;
      d+=15;
    }
  }
    pthread_cancel(pth);


    draw_text(i,1);
    if(lose == 0){
       win_write_line_at(t,4,4,"YOU WIN");
       usleep(3000000);
       return 1;
     }
     if(lose == 1){
       win_write_line_at(t,4,4,"YOU LOOSE");
       usleep(3000000);
       return 0;
     }

  return 1;
}
