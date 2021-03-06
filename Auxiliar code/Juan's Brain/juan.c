
#include "juan.h"




struct termios initial;


void _term_init() {
	struct termios new;	          /*a termios structure contains a set of attributes about
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

void main_juan(Interface *i){
	int quit, game;
	int k;
	char** board;
	int sizeb[2];


 /*We create the maps for the board,score and text and set them on the interface*/
	board = create_map("juan.txt",sizeb);

	set_board(i, board, sizeb[0], sizeb[1]);
	draw_board(i, 1);

	/*_term_init();*/

	sc_rectangle* t;
 	t = get_text(i);
 	if(!t) return;

	win_write_line_at(t,4,4,"Press the space bar to continue");

	printf("\e[?25l");
  fflush(stdout);

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
			int k;
			for(k = 0; k < sizeb[0]; k++){
				free(board[k]);
			}
			free(board);
			break;
		}
	}

/*We create the new map,and draw it in board*/
	board = create_map("juan_board.txt",sizeb);
	set_board(i, board, sizeb[0], sizeb[1]);
	draw_board(i, 1);
	draw_text(i, 1);

	/*We call the game*/
 game = Juan(i);

	if(game == LOOSE){
		for(k = 0; k < sizeb[0]; k++){
			free(board[k]);
		}
		free(board);

		board = create_map("looser.txt",sizeb);
		set_board(i, board, sizeb[0], sizeb[1]);
		draw_board(i, 1);
	}

	if (game == WIN){
		for(k = 0; k < sizeb[0]; k++){
			free(board[k]);
		}
		free(board);

		board = create_map("winner.txt",sizeb);
		set_board(i, board, sizeb[0], sizeb[1]);
		draw_board(i, 1);
		win_write_line_at(t,4,4,"Thanks for playing!");
	}

	tcsetattr(fileno(stdin), TCSANOW, &initial);
	for(k = 0; k < sizeb[0]; k++){
		free(board[k]);
	}

	free(board);

	return;
}




int number_rand(int min, int max){
  return min+(rand()%(max-min+1));
}


int Juan(Interface *in){
  int i, j, number, errs = 0, col, fila, key;
  char numchar[5], errchar[8], answer[5];
  sc_rectangle *t, *s, *b;

  t = get_text(in);
  s = get_score(in);
  b = get_board(in);

  srand(time(NULL));
  win_write_line_at(s, 4, 4,"         RULES");
  win_write_line_at(s, 6, 4,"   Remember the number");
  win_write_line_at(s, 8, 4,"  There are 10 numbers");
	win_write_line_at(s, 10, 4,"   5 fails = lost game");
  win_write_line_at(s, 12, 4," Juan may cough too much");
	win_write_line_at(s, 14, 4,"      And finally...");
  win_write_line_at(s, 16, 4," TRY TO WIN JUAN'S BRAIN");
	win_write_line_at(s, 20, 4," Try 'exit' to exit haha");
  win_write_line_at(s, 22, 4,"Fails : ");

	sprintf(errchar, "%d", errs);
	win_write_line_at(s, 22, 12, errchar);
	win_write_line_at(b, 12, 35, "You have 10 seconds to read the rules");
	usleep(7000000);
	win_write_line_at(b, 12, 35, "                                     ");

  for(i = 0; i < 10; i++){
		draw_board(in, 1);
		draw_text(in, 1);

  	number = number_rand(1000, 9999);
		sprintf(numchar, "%d", number);
		col = number_rand(22, 69);
		fila = number_rand(12, 20);
		win_write_line_at(b, fila, col, numchar);
		usleep(600000);
		win_write_line_at(b, fila, col, "      ");

		if(number == -1) return ERR;

		if(number > 6000){
			for(j = 0; j < 300; j++){
				col = number_rand(4, 79);
				fila = number_rand(1, 20);
				win_write_line_at(b, fila, col, "COUGH");
				usleep(12000);
				}

			win_write_line_at(t, 3, 4, "Juan is coughing too much, you can't concentrate");
			win_write_line_at(t, 4, 4, "You will have to give him something");
			win_write_line_at(t, 5, 4, "Do you want to give Juan a sweet? [y/n]");

			while(1){
				key = _read_key();
				if(key == 'y'){
					win_write_line_at(t, 6, 4, "Juan is getting better...");
					win_write_line_at(t, 7, 4, "You have to answer first without looking:");
					goto here;
				}
				else if(key == 'n'){
					win_write_line_at(t, 6, 4, "You are a bad friend, you are nothing");
					win_write_line_at(t, 7, 4, "You have two points less in this exam");
					usleep(1200000);
					errs += 2;
					sprintf(errchar, "%d", errs);
					win_write_line_at(s, 22, 12, errchar);
					goto compare;
				}
				else{ continue; }
		}
	}

		win_write_line_at(t, 4, 4, "Your answer :");

		here : tcsetattr(fileno(stdin), TCSANOW, &initial);
		fscanf(stdin, "%s", answer);
		_term_init();

		usleep(2000000);
		if(strcmp(answer, "exit") == 0){
			 return WIN;
		 }

    if(strcmp(answer, numchar) != 0){
			errs++;
			sprintf(errchar, "%d", errs);
			win_write_line_at(s, 22, 12, errchar);
		}

		compare : if(5 <= errs){
			draw_board(in, 1);
			draw_text(in, 1);
			win_write_line_at(b, 3, 24, "  YOU HAVE");
			win_write_line_at(b, 4, 24, "   FAILED ");
			win_write_line_at(b, 5, 24, "MUAJAJAJAJA");
			usleep(2000000);
			return LOOSE;
		}
  }
	draw_board(in, 1);
	draw_text(in, 1);
  return WIN;
}
