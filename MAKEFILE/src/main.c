#include "world.h"
#include "play.h"


struct termios initial;


static int Dr[5] = {-1, 1, 0, 0, 0};
static int Dc[5] = {0, 0, 1, -1, 0};
void first_scene(Interface* i){
    char** board;
    char quit;
    int sizeb[2];
		int* pos = (int*)malloc(sizeof(int)*2);
    sc_rectangle* t;

    printf("\e[?25l");
		fflush(stdout);
		if (i == NULL) return -1;


    board = create_map("zoewie",sizeb);

		_term_init();


		draw_score(i,1);


		draw_text(i,1);

    set_player(i,'J',15,64);
		set_board(i,board,sizeb[0],sizeb[1]);
    draw_board(i,1);

    t = get_text(i);


    /*win_write_line_at(t,4,4,"After a long night in Zoewie, it's time to go home");
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
		draw_text(i,1);*/

    win_write_line_at(t,4,4,"Objetive: Go to Plaza de Hispania");

    while(1){
      quit = _read_key();

			if (quit == 'q'){
				tcsetattr(fileno(stdin), TCSANOW, &initial);	/*We now restore the settings we back-up'd
										so that the termial behaves normally when
										the program ends*/
				 return;
			 }

      pos = player_get_position(i);

      if (pos[0] == 15 && pos[1] == 5){
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
    set_player(i,'J',15,64);
		set_board(i,board,sizeb[0],sizeb[1]);
    draw_board(i,1);

    while(1){
      quit = _read_key();

			if (quit == 'q'){
				tcsetattr(fileno(stdin), TCSANOW, &initial);	/*We now restore the settings we back-up'd
										so that the termial behaves normally when
										the program ends*/
				 return;
			 }


      pos = player_get_position(i);

      if (pos[0] == 15 && pos[1] == 5){
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
    set_player(i,'J',15,63);
		set_board(i,board,sizeb[0],sizeb[1]);
    draw_board(i,1);

    while(1){
      quit = _read_key();

      if (quit == 'q'){
				tcsetattr(fileno(stdin), TCSANOW, &initial);	/*We now restore the settings we back-up'd
										so that the termial behaves normally when
										the program ends*/
				 return;
			 }

      pos = player_get_position(i);

      if (pos[1] == 4){
        free (pos);
        break;
      }

      move(i,-quit);
  		fflush(stdout);
    }

		tcsetattr(fileno(stdin), TCSANOW, &initial);	/*We now restore the settings we back-up'd
								so that the termial behaves normally when
								the program ends*/
    return;
}

int initiate_world(Interface *i,World *w){
  char** board;
  char quit;
  char* name = (char*)malloc(sizeof(char)*50);
	char query[100];
  int slot;
  int sizeb[2];
	int* pos = (int*)malloc(sizeof(int)*2);
  sc_rectangle* t;

  printf("\e[?25l");
	fflush(stdout);
	if (i == NULL) return -1;

	_term_init();
  board = create_map("menu",sizeb);


	draw_score(i,1);


	draw_text(i,1);

  set_player(i,'J',11,14);
	set_board(i,board,sizeb[0],sizeb[1]);
  draw_board(i,1);

  t = get_text(i);

  win_write_line_at(t,4,4,"Select an option with the space bar");

  while (1){
    pos = player_get_position(i);
    quit = _read_key();

    if (quit == -NORTH){
        if ((pos[0] - 2) < 10 ) continue;
        else {
          set_player(i,'J',pos[0] - 2,14);
          draw_board(i,1);
        }
    }

    if (quit == -SOUTH){
      if ((pos[0] + 2) > 16) continue;
      else{
        set_player(i,'J',pos[0] + 2,14);
        draw_board(i,1);
      }
    }

    if (quit == 32){

        switch (pos[0]) {
          case 11:
						tcsetattr(fileno(stdin), TCSANOW, &initial);
            draw_text(i,1);
            win_write_line_at(t,4,4,"Introduce your name: ");
            fscanf(stdin,"%s",name);
            draw_text(i,1);
      sloti: win_write_line_at(t,4,4,"Introduce the number of the slot[1/2/3]: ");
            fscanf(stdin,"%d",&slot);
						if(slot <=0 || slot > 3) goto sloti;
            set_name_player(w,name);
            save(w,slot);
            return 1;
          case 13:
						tcsetattr(fileno(stdin), TCSANOW, &initial);
            draw_text (i,1);
    sloto:  win_write_line_at(t,4,4,"Introduce the number of the slot: ");
            fscanf(stdin,"%d",&slot);
						if(slot <=0 || slot > 3) goto sloto;
            load(w,slot);
						Player *pl;
						pl = get_player(w);
						name = get_name(pl);
						sprintf(query,"It's %s your name? [y/n]: ",name);
						win_write_line_at(t,5,4,query);
						slot = _read_key();
						draw_text(i,1);
						if(slot == 'n') goto sloto;
            return 0;
          case 15:
            draw_text(i,1);
            win_write_line_at(t,4,4,"Hello. I'm an useless option.");
            break;
          default:
            continue;
        }
    }
  }
}

void main(){
  World *w;
  Interface *i;
  int res,j;
	char **board;
	char **score;
	char **text;
	int sizeb[2],sizet[2],sizes[2];
	sc_rectangle *t;

	i = inter_create(33,114,0,0,0,86,22,0);

	w = create_world();

	board = create_map("mapa_metro.txt",sizeb);
  score = create_map("score",sizes);
  text = create_map("text",sizet);

	set_board(i,board,sizeb[0],sizeb[1]);
	set_score(i,score,sizes[0],sizes[1]);
	set_text(i,text,sizet[0],sizet[1]);

	t = get_text(i);


  wearetheworld: res = initiate_world(i,w);
  if (res == 1) first_scene (i);
  res = play(w,i);
	if(res == -1){
		draw_text(i,1);
		win_write_line_at(t,4,4,"You have reached 100(%%) alcohol in blood. YOU DIED");
		usleep(5000000);
		draw_text(i,1);
		win_write_line_at(t,4,4,"But you have another try. Load your game.");
		usleep(5000000);
		goto wearetheworld;
	}
  inter_delete(i);

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


	return;

}
