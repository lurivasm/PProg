#include "dani.h"

struct termios initial;



void main_dani(Interface *i){
  FILE *f;
	int quit;
	int j=0,m;
	char** board;
	char** score;
	char** text;
	int sizeb[2],mode;


 /*We create the maps for the board,score and text and set them on the interface*/
	board = create_map("portada",sizeb);


	set_board(i,board,sizeb[0],sizeb[1]);

	draw_board(i,1);

	draw_score(i,1);

	draw_text(i,1);

	initial =_term_init();

	sc_rectangle* t;
 	t = get_text(i);
 	if(!t) return;

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
	set_player(i,'J',4,63);
	draw_board(i,1);

  while(1){
		m = _read_key();
		/*pressing q it exits*/
		if (m == 'q')	break;

     move(i,-m);

   }

 return;




}
