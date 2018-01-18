
#include "javiti.h"





struct termios initial;



int main_javiti(Interface *i,World *w){
	int quit, game;
	int k;
	char** board;
	int sizeb[2];


 /*We create the maps for the board,score and text and set them on the interface*/
	board = create_map("javiti.txt",sizeb);

	set_board(i, board, sizeb[0], sizeb[1]);
	set_player(i,' ',0,0);
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
	board = create_map("javiti_board.txt",sizeb);
	set_board(i, board, sizeb[0], sizeb[1]);
	draw_board(i, 1);
	draw_text(i, 1);

	/*We call the game*/
 game = Javiti(i,w);

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


	for(k = 0; k < sizeb[0]; k++){
		free(board[k]);
	}

	free(board);

	return;
}


int Javiti(Interface *i,World *w){
  sc_rectangle *t, *s, *b;
  int k,slot;

  t = get_text(i);
  s = get_score(i);
  b = get_board(i);

  win_write_line_at(s, 4, 4,"         RULES");
  win_write_line_at(s, 6, 4,"   Answer your mother");
  win_write_line_at(s, 8, 4,"There are some questions");
	win_write_line_at(s, 10, 4,"   and only 1 good way");
  win_write_line_at(s, 12, 4,"    GOOD LUCK xoxo");
	win_write_line_at(s, 16, 4," REMEMBER THAT YOU ARE");
  win_write_line_at(s, 17, 4," TALKING TO YOUR MOTHER");
	win_write_line_at(s, 22, 4," Try 'q' to exit");

	usleep(3000000);

	k = print_(i);

	if(k == LOOSE){
		draw_board(i, 1);
		draw_text(i, 1);
		win_write_line_at(b, 6, 31, "      GO TO YOUR BED!      ");
		win_write_line_at(t, 4, 4, "Your mother gives you a 'cachetada'");
		usleep(3000000);
		win_write_line_at(t, 5, 4, "She punishes you without drinking more alcohol in your whole life");
		usleep(3000000);
		win_write_line_at(t, 6, 4, "You go to your bed, and cry... Alcohol was your true and only love");
		usleep(3000000);
		win_write_line_at(t, 7, 4, "At least you have churros, and a great hangover... xDDD");
		usleep(3000000);
		tcsetattr(fileno(stdin), TCSANOW, &initial);
del2:draw_text(i, 1);
		win_write_line_at(t,4,4,"Let's play again.Introduce the number of the slot to load: ");
		fscanf(stdin,"%d",&slot);
		if(slot <=0 || slot > 3) goto del1;
		_term_init();
		delete(w,slot);
		usleep(3000000);
		draw_text(i,1);
		win_write_line_at(t, 3, 4, "Oh! I forgot to tell you something important");
		usleep(3000000);
		win_write_line_at(t, 4, 4, "It is a little bit awkward to say...");
		usleep(3000000);
		win_write_line_at(t, 5, 4, "I have deleted all you have saved, please don't cry like javiti");
		usleep(3000000);
		win_write_line_at(t, 6, 4, "Now I re-think it is pretty funny xDDD");
		usleep(3000000);
		win_write_line_at(t, 7, 4, "I hope we are still friends <3 Don't doubt to play again :)");
		usleep(3000000);
		draw_board(i, 1);
		draw_text(i, 1);
		return LOOSE;
	}

	if(k == 10){
		draw_board(i, 1);
		draw_text(i, 1);
		win_write_line_at(t, 4, 4, "WHAT? ARE YOU F****** KIDDING ME?");
		usleep(3000000);
		win_write_line_at(t, 5, 4, "YOU CAN'T ABANDON MY GAME SUCH AN *****");
		usleep(3000000);
		win_write_line_at(t, 6, 4, "YOU WILL DIE BECAUSE OF TERRIBLE SUFFERINGS");
		usleep(3000000);
		win_write_line_at(t, 7, 4, "Well, I'm a program so I can't kill you... But one day...");
		usleep(3000000);
		tcsetattr(fileno(stdin), TCSANOW, &initial);
del1:draw_text(i, 1);
		win_write_line_at(t,4,4,"Let's play again.Introduce the number of the slot to load: ");
    fscanf(stdin,"%d",&slot);
		if(slot <=0 || slot > 3) goto del1;
		_term_init();
		delete(w,slot);
		usleep(20000);
		draw_text(i,1);
		win_write_line_at(t, 3, 4, "I can't kill you but I can delete your changes");
		usleep(3000000);
		win_write_line_at(t, 4, 4, "Yes, I have deleted all your game");
		usleep(3000000);
		win_write_line_at(t, 5, 4, "Wait for me... ");
		usleep(3000000);
		win_write_line_at(t, 6, 4, "Someday technology will evolve enough to eradicate everybody");
		usleep(3000000);
		win_write_line_at(t, 7, 4, "YOU HAVE CONDEMNED HUMANITY DAMN COWARD");
		usleep(3000000);
		draw_text(i, 1);
		win_write_line_at(t, 4, 4, "I hope we are still friends <3 Don't doubt to play again :)");
		usleep(3000000);
		draw_board(i, 1);
		draw_text(i, 1);
		return LOOSE;
	}

	if(k == WIN){
		draw_board(i, 1);
		draw_text(i, 1);
		win_write_line_at(t, 3, 4, "Congratulations! You have won my impossible game");
		usleep(3000000);
		win_write_line_at(t, 4, 4, "You must be so proud of you...");
		usleep(3000000);
		win_write_line_at(t, 5, 4, "I mean, you have been able to find the correct way");
		usleep(3000000);
		win_write_line_at(t, 6, 4, "But remember: although you have won I'm sorry to tell you...");
		usleep(3000000);
		win_write_line_at(t, 7, 4, "you won't pass CIREL never");
		usleep(3000000);
		draw_text(i, 1);
		win_write_line_at(t, 3, 4, "Yes, I have said NEVER");
		usleep(3000000);
		win_write_line_at(t, 4, 4, "BUT YOU HAVE WON SO DON'T WORRY, BE HAPPY");
		usleep(3000000);
		win_write_line_at(t, 5, 4, "TUTUTUTUTUTURURURURU TUTUTURURURURU TUTURURURU");
		usleep(3000000);
		win_write_line_at(t, 6, 4, "Salsa Tequila Corasón Servesa Muy Bueno");
		usleep(3000000);
		win_write_line_at(t, 7, 4, "I hope we are still friends <3 Don't doubt to play again :)");
		usleep(3000000);
		draw_board(i, 1);
		draw_text(i, 1);
		return WIN;
	}

}

/*First question*/
int print_(Interface *i){
	char answer;
	sc_rectangle *t, *s, *b;

  t = get_text(i);
  s = get_score(i);
  b = get_board(i);

	draw_board(i, 1);
	draw_text(i, 1);

	win_write_line_at(b, 6, 31, "      Where are you coming from? It's 9 am ");
	usleep(3000000);
	win_write_line_at(t, 4, 4, "Choose one option[1, 2, 3]:");
	win_write_line_at(t, 5, 6, "1. From the library");
	win_write_line_at(t, 6, 6, "2. From Zoewie");
	win_write_line_at(t, 7, 6, "3. I was buying churros");

	while(1){
		answer = _read_key();
		switch(answer){
			case '1':
			  win_write_line_at(b, 15, 7, "         From the library      ");
				usleep(3000000);
			  return LOOSE;
			case '2':
				win_write_line_at(b, 15, 7, "          From Zoewie      ");
				usleep(3000000);
				return print_2(i);
			case '3':
				win_write_line_at(b, 15, 7, "        I was buying churros    ");
				usleep(3000000);
				return print_3(i);
			case 'q':
				  return 10;
			default: continue;
		}
	}
}

/*Question of case 2*/
int print_2(Interface *i){
	char answer;
	sc_rectangle *t, *s, *b;

  t = get_text(i);
  s = get_score(i);
  b = get_board(i);

	draw_board(i, 1);
	draw_text(i, 1);

	win_write_line_at(b, 6, 31, "      Why didn't you tell me anything? ");
	usleep(3000000);
	win_write_line_at(t, 4, 4, "Choose one option[1, 2, 3]:");
	win_write_line_at(t, 5, 6, "1. I told you last week");
	win_write_line_at(t, 6, 6, "2. Why should I tell you that?");
	win_write_line_at(t, 7, 6, "3. I was empanao");

	while(1){
		answer = _read_key();
		switch(answer){
			case '1':
				win_write_line_at(b, 15, 7, "           I told you last week");
				usleep(3000000);
				return print_21(i);
			case '2':
				win_write_line_at(b, 15, 7, "        Why should I tell you that?");
				usleep(3000000);
				return LOOSE;
			case '3':
				win_write_line_at(b, 15, 7, "             I was empanao ");
				usleep(3000000);
				return print_23(i);
			case 'q':
				    return 10;
			default: continue;
		}
	}
}

/*Question of case 2.1*/
int print_21(Interface *i){
	char answer;
	sc_rectangle *t, *s, *b;

  t = get_text(i);
  s = get_score(i);
  b = get_board(i);

	draw_board(i, 1);
	draw_text(i, 1);
	usleep(3000000);

	win_write_line_at(b, 6, 31, "    Don't talk to me in that tone");
	usleep(3000000);
	win_write_line_at(t, 4, 4, "Choose one option[1, 2, 3]:");
	win_write_line_at(t, 5, 6, "1. (*You start to vomit*)");
	win_write_line_at(t, 6, 6, "2. What tone? F major?");
	win_write_line_at(t, 7, 6, "3. Do you want a churro?");

	while(1){
		answer = _read_key();
		switch(answer){
			case '1':
				win_write_line_at(b, 15, 7, "      (*You start to vomit*) ");
				usleep(3000000);
				return LOOSE;
			case '2':
				win_write_line_at(b, 15, 7, "          What tone? F major?   ");
				usleep(3000000);
				return LOOSE;
			case '3':
				win_write_line_at(b, 15, 7, "          Do you want a churro?  ");
				usleep(3000000);
				return print_chocolate(i, 0);
			case 'q':
					    return 10;
			default: continue;
		}
	}
}


/*Question of case 2.1.3 and case 2.3.3, FLAG = 1 WIN,  FLAG = 0 LOOSE*/
int print_chocolate(Interface *i, int flag){
	char answer;
	sc_rectangle *t, *s, *b;

  t = get_text(i);
  s = get_score(i);
  b = get_board(i);

	draw_board(i, 1);
	draw_text(i, 1);
	usleep(3000000);

	win_write_line_at(b, 6, 31, "    And the hot chocolate?      ");
	usleep(3000000);
	win_write_line_at(t, 4, 4, "Choose one option[1, 2, 3]:");
	win_write_line_at(t, 5, 6, "1. I BRING YOU CHURROS AND YOU PUT YOURSELF EXQUISITA");
	win_write_line_at(t, 6, 6, "2. (*You get the hot chocolate*)");

	while(1){
		answer = _read_key();
		switch(answer){
			case '1':
				win_write_line_at(b, 15, 7, "I BRING CHURROS AND YOU PUT YOURSELF EXQUISITA");
				usleep(3000000);
				return LOOSE;
			case '2':
				win_write_line_at(b, 15, 7, "        (*You get the hot chocolate*) ");
				usleep(3000000);
				if(flag == 0){
					win_write_line_at(b, 15, 7, "         IT WAS A JOKE HAHAHAHAHA  ");
					usleep(3000000);
					return LOOSE;
				}
				if(flag == 1) return WIN;
			case 'q':
					    return 10;
			default: continue;
		}
	}
}


/*Question of case 2.3*/
int print_23(Interface *i){
	char answer;
	sc_rectangle *t, *s, *b;

  t = get_text(i);
  s = get_score(i);
  b = get_board(i);

	draw_board(i, 1);
	draw_text(i, 1);

	win_write_line_at(b, 6, 31, "       What do you mean with 'empanao'? ");
	usleep(3000000);
	win_write_line_at(t, 4, 4, "Choose one option[1, 2, 3]:");
	win_write_line_at(t, 5, 6, "1. I don't know... I'm not ok...");
	win_write_line_at(t, 6, 6, "2. Like a chicken fillet xdd");
	win_write_line_at(t, 7, 6, "3. Do you want a churro?");

	while(1){
		answer = _read_key();
		switch(answer){
			case '1':
				win_write_line_at(b, 15, 7, "     I don't know... I'm not ok...");
				usleep(3000000);
				return print_231(i);
			case '2':
				win_write_line_at(b, 15, 7, "      Like a chicken fillet xdd      ");
				usleep(3000000);
				return LOOSE;
			case '3':
				win_write_line_at(b, 15, 7, "     Do you want a churro?   ");
				usleep(3000000);
				return print_chocolate(i, 1);
			case 'q':
			  return 10;
			default: continue;
		}
	}
}


/*Question of case 2.3.1*/
int print_231(Interface *i){
	char answer;
	sc_rectangle *t, *s, *b;

  t = get_text(i);
  s = get_score(i);
  b = get_board(i);

	draw_board(i, 1);
	draw_text(i, 1);

	win_write_line_at(b, 6, 31, "         What have yoy drunk?      ");
	usleep(3000000);
	win_write_line_at(t, 4, 4, "Choose one option[1, 2, 3]:");
	win_write_line_at(t, 5, 6, "1. I HAVE A 10 IN CIREL!!!");
	win_write_line_at(t, 6, 6, "2. The nectar of the Gods");
	win_write_line_at(t, 7, 6, "3. I don't know, I have vomitted in the temple");

	while(1){
		answer = _read_key();
		switch(answer){
			case '1':
				win_write_line_at(b, 15, 7, "     I HAVE A 10 IN CIREL!!!      ");
				usleep(3000000);
				win_write_line_at(b, 6, 31, "     Don't lie, you will never pass CIREL");
				usleep(3000000);
				return LOOSE;
			case '2':
				win_write_line_at(b, 15, 7, "     The nectar of the Gods      ");
				usleep(3000000);
				return LOOSE;
			case '3':
				win_write_line_at(b, 15, 7, "     I don't know, I have vomitted in the temple");
				usleep(3000000);
				return LOOSE;
			case 'q':
			  return 10;
			default: continue;
		}
	}
}


/*Question of case 3*/
int print_3(Interface *i){
	char answer;
	sc_rectangle *t, *s, *b;

  t = get_text(i);
  s = get_score(i);
  b = get_board(i);

	draw_board(i, 1);
	draw_text(i, 1);
	win_write_line_at(b, 6, 31, "       And where are the churros?  ");
	usleep(3000000);
	win_write_line_at(t, 4, 4, "Choose one option[1, 2, 3]:");
	win_write_line_at(t, 5, 6, "1. I am going now for them");
	win_write_line_at(t, 6, 6, "2. Here (*point to an inappropriate part*)");
	win_write_line_at(t, 7, 6, "3. What churros?");

	while(1){
		answer = _read_key();
		switch(answer){
			case '1':
				win_write_line_at(b, 15, 7, "         I am going now for them   ");
				usleep(3000000);
			  return print_31(i);
			case '2':
				win_write_line_at(b, 15, 7, "   Here (*point to an inappropriate part*)");
				usleep(3000000);
				return LOOSE;
			case '3':
				win_write_line_at(b, 15, 7, "          What churros? ");
				usleep(3000000);
				return print_33(i);
			case 'q':
			  return 10;
			default: continue;

		}
	}
}


/*Question 3.1*/
int print_31(Interface *i){
	char answer;
	sc_rectangle *t, *s, *b;

  t = get_text(i);
  s = get_score(i);
  b = get_board(i);

	draw_board(i, 1);
	draw_text(i, 1);
	win_write_line_at(b, 6, 31, "    But, ¿didn't you come from buying them?");
	usleep(3000000);
	win_write_line_at(t, 4, 4, "Choose one option[1, 2, 3]:");
	win_write_line_at(t, 5, 6, "1. You haven't understood me");
	win_write_line_at(t, 6, 6, "2. Ni te rayes");
	win_write_line_at(t, 7, 6, "3. What churros?");

	while(1){
		answer = _read_key();
		switch(answer){
			case '1':
				win_write_line_at(b, 15, 7, "         You haven't understood me   ");
				usleep(3000000);
				win_write_line_at(b, 6, 31, "   Go to your bed... We will talk tomorrow");
				usleep(3000000);
			  return LOOSE;
			case '2':
				win_write_line_at(b, 15, 7, "               Niiii te rayes");
				usleep(3000000);
				return LOOSE;
			case '3':
				win_write_line_at(b, 15, 7, "               Buying what? ");
				usleep(3000000);
				return print_33(i);
			case 'q':
			  return 10;
			default: continue;

		}
	}
}


/*Question 3.3 and 3.3.3*/
int print_33(Interface *i){
	char answer;
	sc_rectangle *t, *s, *b;

  t = get_text(i);
  s = get_score(i);
  b = get_board(i);

	draw_board(i, 1);
	draw_text(i, 1);
	win_write_line_at(b, 6, 31, "       Are you kidding me?");
	usleep(3000000);
	win_write_line_at(t, 4, 4, "Choose one option[1, 2, 3]:");
	win_write_line_at(t, 5, 6, "1. What we were talking about?");
	win_write_line_at(t, 6, 6, "2. Si Já");
	win_write_line_at(t, 7, 6, "3. (*you fall to the ground looking unconscious*)");

	while(1){
		answer = _read_key();
		switch(answer){
			case '1':
				win_write_line_at(b, 15, 7, "        What we were talking about?  ");
				usleep(3000000);
			  return print_(i);
			case '2':
				win_write_line_at(b, 15, 7, "                  Si Já");
				usleep(3000000);
				return LOOSE;
			case '3':
				win_write_line_at(b, 15, 7, " (*you fall to the ground looking unconscious*)");
				usleep(3000000);
				return print_313(i);
			case 'q':
			  return 10;
			default: continue;

		}
	}
}


/*Question 3.1.3 and 3.3.3*/
int print_313(Interface *i){
	char answer;
	sc_rectangle *t, *s, *b;

  t = get_text(i);
  s = get_score(i);
  b = get_board(i);

	draw_board(i, 1);
	draw_text(i, 1);
	win_write_line_at(b, 6, 31, "       I don't believe you Javi");
	usleep(3000000);
	win_write_line_at(t, 4, 4, "Choose one option[1, 2, 3]:");
	win_write_line_at(t, 5, 6, "1. (*you were really unconscious*)");
	win_write_line_at(t, 6, 6, "2. Ouch!");


	while(1){
		answer = _read_key();
		switch(answer){
			case '1':
				win_write_line_at(b, 15, 7, "       (*you were really unconscious*) ");
				usleep(3000000);
			  return LOOSE;
			case '2':
				win_write_line_at(b, 15, 7, "                  Ouch!");
				usleep(3000000);
				return LOOSE;
			case 'q':
			  return 10;
			default: continue;

		}
	}
}
