#include "world.h"
#include "play.h"


struct termios initial;



void _term_init() {
	struct termios new;/*a termios structure contains a set of attributes about
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

static int Dr[5] = {-1, 1, 0, 0, 0};
static int Dc[5] = {0, 0, 1, -1, 0};
void first_scene(Interface* i){
    char** board;
    char** score;
    char** text;
    char quit;
    int sizeb[2],sizes[2],sizet[2],pos[2];
    sc_rectangle* t;

    printf("\e[?25l");
		fflush(stdout);
		if (i == NULL) return -1;

    score = create_map("score",sizes);
    text = create_map("text",sizet);
    board = create_map("zoewie",sizeb);


		set_score(i,score,sizes[0],sizes[1]);
		draw_score(i,1);

		set_text(i,text,sizet[0],sizet[1]);
		draw_text(i,1);

    set_player(i,'J',16,64);
		set_board(i,board,sizeb[0],sizeb[1]);
    draw_board(i,1);

    t = get_text(i);


    win_write_line_at(t,4,4,"After a long night in Zoewie, it's time to go home");
    usleep(4000000);
		draw_text(i,1);

    win_write_line_at(t,4,4,"But Javiti has drunk too much...");
    usleep(4000000);
		draw_text(i,1);

    win_write_line_at(t,4,4,"Javiti: Catiti, do you come with me?");
    usleep(4000000);
		draw_text(i,1);

    win_write_line_at(t,4,4,"Catiti: Yes, but promise me that you aren't going to fall asleep");
    usleep(4000000);
		draw_text(i,1);

    win_write_line_at(t,4,4,"Javiti: Of course. I'm not an idiot.");
    usleep(4000000);
		draw_text(i,1);

    win_write_line_at(t,4,4,"Objetive: Go to Plaza de Hispania");

    while(1){
      quit = _read_key();

      if (quit == q) return;

      pos = player_get_position(i);

      if (pos[0] == 16 && pos[1] == 6){
        free (pos);
        break;
      }

      move(i,-quit);
  		fflush(stdout);
    }
    int j;
  	for(j = 0;j<sizeb[0];j++){
  		free(board[j]);
  	}
    free(board);

    board = create_map("street",sizeb);
    set_player(i,'J',16,64);
		set_board(i,board,sizeb[0],sizeb[1]);
    draw_board(i,1);

    while(1){
      quit = _read_key();

      if (quit == q) return;

      pos = player_get_position(i);

      if (pos[0] == 16 && pos[1] == 6){
        free (pos);
        break;
      }

      move(i,-quit);
  		fflush(stdout);
    }
    for(j = 0;j<sizeb[0];j++){
  		free(board[j]);
  	}
    free(board);

    board = create_map("metro",sizeb);
    set_player(i,'J',16,64);
		set_board(i,board,sizeb[0],sizeb[1]);
    draw_board(i,1);

    while(1){
      quit = _read_key();

      if (quit == q) return;

      pos = player_get_position(i);

      if (pos[1] == 4){
        free (pos);
        break;
      }

      move(i,-quit);
  		fflush(stdout);
    }

    return;
}

int iniate_world(Interface *i,World *w){
  char** board;
  char** score;
  char** text;
  char quit;
  char name[50];
  int slot;
  int sizeb[2],sizes[2],sizet[2],pos[2];
  sc_rectangle* t;

  printf("\e[?25l");
	fflush(stdout);
	if (i == NULL) return -1;

  score = create_map("score",sizes);
  text = create_map("text",sizet);
  board = create_map("portada",sizeb);

	set_score(i,score,sizes[0],sizes[1]);
	draw_score(i,1);

	set_text(i,text,sizet[0],sizet[1]);
	draw_text(i,1);

  set_player(i,'J',12,14);
	set_board(i,board,sizeb[0],sizeb[1]);
  draw_board(i,1);

  t = get_text(i);

  win_write_line_at(t,4,4,"Select an option with the space bar");

  while (1){
    pos = player_get_position(i);
    quit = _read_key();

    if (quit == -NORTH){
        if ((pos[0] - 2) < 11 ) continue;
        else {
          set_player(i,'J',pos[0] - 2,14);
          draw_board(i,1);
        }
    }

    if (quit == -SOUTH){
      if ((pos[0] + 2) > 17) continue;
      else{
        set_player(i,'J',pos[0] + 2,14);
        draw_board(i,1);
      }
    }

    if (quit == 32){
        switch (pos[0]) {
          case 12:
            draw_text(i,1);
            win_write_line_at(t,4,4,"Introduce your name: ");
            fscanf(stdin,"%s",name);
            draw_text(i,1);
            win_write_line_at(t,4,4,"Introduce the number of the slot: ");
            fscanf(stdin,"%d",slot);
            w = create_world();
            set_name_player(w,name);
            save(w,slot);
            return 1;
          case 14:
            draw_text (i,1);
            win_write_line_at(t,4,4,"Introduce the number of the slot: ");
            fscanf(stdin,"%d",slot);
            w = create_world();
            load(w,slot);
            return 0;
          case 16:
            draw_text(i,1);
            win_write_line_at(t,4,4,"Hello. I'm an useless option.");
            continue;
          default:
            continue;
        }
    }
  }
}

void main(){
  World *w;
  Interface *i;
  int res;
  _term_init();
	i = inter_create(33,114,0,0,0,86,22,0);

  res = iniate_world(i,w);
  if (res == 1) first_scene (i);
  play(i,w);
  inter_delete(i);

	tcsetattr(fileno(stdin), TCSANOW, &initial);
	return;

}
