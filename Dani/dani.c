#include "dani.h"

struct termios initial;

/*int tim = 100000;

void laser(void *i){
  int cont = 0,r,c;
  sc_rectangle *b,*t;
  b = get_board(i);
  t = get_text(i);

  while(cont !=5){
    r = 20;
    c = rand()%84;
    win_write_char_at(b,20,c,'o');
    win_write_char_at(b,5,c,'J');
    while(r != 1){
      if(r == 5){
        cont = 4;
        win_write_line_at(t,4,4,"YOU LOST!");
        break;
      }
      win_write_char_at(b,r,c,' ');
      win_write_char_at(b,r-1,c,'o');
      r--;

      usleep(tim);
    }
    win_write_char_at(b,r,c,' ');
    cont++;
  }
  pthread_exit (NULL);
  return;
}
*/

void main_dani(Interface *i){

	int quit;
	int m;
  int *p;
  p = (int*)malloc(sizeof(int)*2);
	char** board;
	int sizeb[2];


 /*We create the maps for the board,score and text and set them on the interface*/
	board = create_map("portada",sizeb);


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
	if (quit == 'q') {
		inter_delete(i);
    tcsetattr(fileno(stdin), TCSANOW, &initial);	/*We now restore the settings we back-up'd
							  so that the termial behaves normally when
							  the program ends */
    return;
  }
	/*if you press the space bar,you move foward*/
	if(quit == 32){
		free(board);
		break;
	}
	}

  draw_text(i,1);

  board = create_map("bar",sizeb);

  set_board(i,board,sizeb[0],sizeb[1]);
	set_player(i,'J',2,62);
	draw_board(i,1);

  win_write_line_at(t,4,4,"You are in the queue to enter a bar.");
  win_write_line_at(t,5,4,"There must be a way to enter avoiding the queue...");
  usleep(4000000);
  win_write_line_at(s,4,4,"Find a way to ");
  win_write_line_at(s,5,4,"enter the bar ");
  win_write_line_at(s,6,4,"and sit in front");
  win_write_line_at(s,7,4,"of the barman(S)");
  while(1){
		m = _read_key();
		/*pressing q it exits*/
		if (m == 'q')	break;

     move(i,-m);
     p = player_get_position(i);
     if(p[0] == 10 && p[1] == 21){
       break;
     }

   }
 draw_text(i,1);
 draw_score(i,1);

 win_write_line_at(t,4,4,"You have a sit and look at the person at your right");
 win_write_line_at(t,5,4,"He suddenly looks at you and starts talking");
 usleep(4000000);
 draw_text(i,1);
 win_write_line_at(t,4,4,"D : Hey bb,you look amazing tonight.What are you doing in this bar?");
 usleep(4000000);
 win_write_line_at(t,5,4,"J : Eeh sorry,I think you're wrong,I'm a boy");
 usleep(4000000);
 win_write_line_at(t,6,4,"D : Hahahaha,you're funny,but I can clearly see that you're a girl");
 usleep(4000000);
 win_write_line_at(t,7,4,"J : No,I'm not");
 usleep(4000000);
 draw_text(i,1);
 win_write_line_at(t,4,4,"D : Look at the mirror right there");
 usleep(4000000);
 win_write_line_at(t,5,4,"J :WTF why would you put a mirror in the bar's counter? ");
 usleep(4000000);
 win_write_line_at(t,6,4,"D :That's because the barman loves to spend the day watching himself there");
 usleep(4000000);
 win_write_line_at(t,7,4,"Santini :Yes,I love that.");
 usleep(4000000);
 draw_text(i,1);
 win_write_line_at(t,4,4,"D : Well,look at the mirror please");
 usleep(4000000);
 win_write_line_at(t,5,4,"You look at it and you discover horrified that you are a GIRL!");
 usleep(4000000);
 win_write_line_at(t,6,4,"D : Well,let's stop making jokes.Do you wnat to dance with me? ( ͡° ͜ʖ ͡°) ");
 usleep(4000000);
 while(1){
   win_write_line_at(t,7,4,"Press the space bar to start avoiding Dani's flirting chips");
      m = _read_key();
   /*pressing q it exits*/
    if (m == 'q')	break;
    if(m == 32){
      dani(i);
      break;
    }
 }


 return;


}


void dani(Interface *i){
    char **board;
    int sizeb[2];

    board = create_map("esquivafichas",sizeb);
    set_board(i,board,sizeb[0],sizeb[1]);
  	set_player(i,'J',1,42);
  	draw_board(i,1);









  return;
}
