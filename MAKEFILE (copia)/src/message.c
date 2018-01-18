/*DECRYPT VIC'S MESSAGE*/
/*All the int functions return -1 or ERR in case of memory error*/
#include "message.h"

struct _message{
  char *coded;           /*The coded message*/
  char *decoded;         /*The decoded message*/
};

struct _game{
  Message *m[10];
  int correct, incorrect;
};

struct termios initial;


int main_vic(Interface *i){
	int quit, game;
	int k;
	char** board;
	int sizeb[2];


 /*We create the maps for the board,score and text and set them on the interface*/
	board = create_map("vic.txt",sizeb);

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
			   return 1;
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
	board = create_map("vic_board.txt",sizeb);
	set_board(i, board, sizeb[0], sizeb[1]);
	draw_board(i, 1);
	draw_text(i, 1);

	/*We call the game*/
 game = Vic(i);

	if(game == LOOSE){
		for(k = 0; k < sizeb[0]; k++){
			free(board[k]);
		}
		free(board);

		board = create_map("looser.txt",sizeb);
		set_board(i, board, sizeb[0], sizeb[1]);
		draw_board(i, 1);
    tcsetattr(fileno(stdin), TCSANOW, &initial);
    usleep(3000000);
  	for(k = 0; k < sizeb[0]; k++){
  		free(board[k]);
  	}

  	free(board);

  	return 0;
	}

	if (game == 1){
		for(k = 0; k < sizeb[0]; k++){
			free(board[k]);
		}
		free(board);

		board = create_map("winner.txt",sizeb);
		set_board(i, board, sizeb[0], sizeb[1]);
		draw_board(i, 1);
		win_write_line_at(t,4,4,"Thanks for playing!");
    usleep(3000000);
    tcsetattr(fileno(stdin), TCSANOW, &initial);
  	for(k = 0; k < sizeb[0]; k++){
  		free(board[k]);
  	}

  	free(board);

  	return 1;
	}


}


/***************************************************************/
/*Inicialization of a game struct with the array of sentences*/
Game *game_ini(char *file){
  if(!file) return NULL;

  Game *g;
  g = (Game*)malloc(sizeof(Game));
  if(!g) return NULL;

  if(message_set(g->m, file) == ERR) return NULL;
  g->correct = 0;
  g->incorrect = 0;

  return g;
}

/***************************************************************/
/*Last game*/
int Vic(Interface *in){
    char f[3];
    int fails, i, comp, fila, cont = 0, number;
    char *answer;
    Game *g;

    sc_rectangle *t, *s, *b;

    t = get_text(in);
    s = get_score(in);
    b = get_board(in);

    srand(time(NULL));
    win_write_line_at(s, 4, 4,"         RULES");
    win_write_line_at(s, 6, 4," Respect capital letters");
    win_write_line_at(s, 8, 4,"There are strange things");
    win_write_line_at(s, 10, 4,"Respect puntuation marks");
    win_write_line_at(s, 12, 4,"   3 fails = lost game");
    win_write_line_at(s, 14, 4,"      And finally...");
    win_write_line_at(s, 15, 4," ENJOY TALKING WITH VIC");
    win_write_line_at(s, 20, 4,"Failed sentences: ");

    usleep(200000);


    fails = 0;
    fila = 8;
    sprintf(f, "%d", fails);
    win_write_line_at(s, 20, 22, f);
    win_write_line_at(t, 4, 4, "Your answer :");

    answer = (char*)malloc(sizeof(char)*200);
    if(!answer) return ERR;

    /*We choose the file of Vic's sentences randomly*/
    number = number_randd(1, 3);
    if(number == 1){
      g = game_ini("messages.txt");
      if(!g) {
        free(answer);
        return ERR;
      }
    }

    else if(number == 2){
      g = game_ini("messages1.txt");
      if(!g) {
        free(answer);
        return ERR;
      }
    }

    else if(number == 3){
      g = game_ini("messages2.txt");
      if(!g) {
        free(answer);
        return ERR;
      }
    }


    for(i = 0; i < 10; i++){
      win_write_line_at(b, 5, 25, "typing...");
      usleep(3000000);
      win_write_line_at(b, 5, 25, "online    ");
      win_write_line_at(b, fila, 3, g->m[i]->coded);
      fila += 2;
      cont++;
      _move_to(t, 4, 18);
      tcsetattr(fileno(stdin), TCSANOW, &initial);
      fgets(answer, 100, stdin);

      if(*answer == 'q'){
        return WIN;
      }

      _term_init();

      win_write_line_at(b, fila, 8, answer);
      fila += 2;
      comp = message_compare(g->m[i], answer);
      win_write_line_at(t, 4, 18, "                                                                  ");

      /*Case of error*/
      if(comp == ERR) {
        message_array_destroy(g->m);
        free(g);
        free(answer);
        return ERR;
      }
      usleep(2000000);

      /*Cleaning the board in order to show new messages*/
      if(cont == 3){
        cont = 0;
        fila = 8;
        draw_board(in, 1);
      }

      /*The answer is incorrect*/
      if(comp == 1){
        fails++;
        sprintf(f, "%d", fails);
        win_write_line_at(s, 20, 22, f);


        g->incorrect++;
        if(g->incorrect == 3){
          win_write_line_at(b, fila, 3, "Ohh f*** offu idsiot xddd");
          usleep(2000000);

          free(g);
          free(answer);
          return 0;
        }
        continue;
      }
      /*The answer is correct*/
      g->correct++;

    }

    win_write_line_at(b, fila, 3, "U ar soo cute:)");
    usleep(2000000);

    free(g);
    free(answer);
    return 1;
}

/***************************************************************/
/*Random function*/
int number_randd(int min, int max){
  return min+(rand()%(max-min+1));
}


/***************************************************************/
/*Initialization of a message*/
Message *message_ini(){
  Message *m = (Message*)malloc(sizeof(Message));
  if(!m) return NULL;

  m->coded = NULL;
  m->decoded = NULL;
  return m;
}


/***************************************************************/
/*Destruction of messages*/
void message_destroy(Message *m){
  if(!m) return;
  if(!m->coded){
    if(!m->decoded){
      free(m);
      return;
    }
    free(m->decoded);
    free(m);
    return;
  }

  if(!m->decoded){
    free(m->coded);
    free(m);
    return;
  }

  free(m->coded);
  free(m->decoded);
  free(m);
}


/***************************************************************/
/*Destruction of an array of messages*/
void message_array_destroy(Message **m){
  if(!m) return;
  int i;

  for(i = 0; i < 10; i++) message_destroy(m[i]);
  free(m);
}


/***************************************************************/
/*Read from the file and set the messages and their numbers*/
int message_set(Message **m, char *file){
  if(!file) return ERR;
  int i = 0, j;
  char *aux, *auxcoded, *auxdecoded;
  FILE *f;

  f = fopen(file,"r");
  if(!f) return ERR;

  aux = (char*)malloc(sizeof(char)*500);
  if(!aux){
    fclose(f);
    return ERR;
  }


  while(!feof(f) && i < 10){
    m[i] = message_ini();
    if(m[i] == NULL){
      for(j = i -1; j == 0; j--) message_destroy(m[i]);
      free(aux);
      free(auxcoded);
      free(auxdecoded);
      fclose(f);
      return ERR;
    }
    m[i]->coded = (char*)malloc(sizeof(char)*500);
    if(!m[i]->coded){
      free(aux);
      fclose(f);
      return ERR;
    }

    m[i]->decoded = (char*)malloc(sizeof(char)*500);
    if(!m[i]->decoded){
      free(aux);
      free(m[i]->coded);
      fclose(f);
      return ERR;
    }

    fgets(aux, 500, f);

    auxcoded = strtok(aux, "/");
    if(!auxcoded){
      free(aux);
      fclose(f);
      return ERR;
    }

    auxdecoded = strtok(NULL, "/");
    if(!auxdecoded){
      free(aux);
      fclose(f);
      return ERR;
    }
    strcpy(m[i]->coded, auxcoded);
    strcpy(m[i]->decoded, auxdecoded);
    i++;
  }

  free(aux);
  fclose(f);
  return 1;
}


/*It returns 0 if they are exactly the same and 1 if they're not*/
int message_compare(Message *m, char* answer){
  if(!m || !answer) return ERR;
   return (strcmp(m->decoded, answer) == 0) ? 0 : 1;
}




/***************************************************************/
/*The minigame without interface*/
int message_game(char *file){
  if(!file) return ERR;

  int comp, i;
  char *answer;
  Game *g;

  answer = (char*)malloc(sizeof(char)*200);
  if(!answer) return ERR;

  g = game_ini(file);
  if(!g) {
    free(answer);
    return ERR;
  }

  for(i = 0; i < 10; i++){

    fprintf(stdout, "%s\n", g->m[i]->coded);
  }
  for(i = 0; i < 10; i++){
    fprintf(stdout, "\nVic: %s\nYou: ", g->m[i]->coded);
    fgets(answer, 100, stdin);

    comp = message_compare(g->m[i], answer);

    /*Case of error*/
    if(comp == ERR) {
      message_array_destroy(g->m);
      free(g);
      free(answer);
      return ERR;
    }

    /*The answer is incorrect*/
    if(comp == 1){
      fprintf(stdout, "Vic(angry): 'That 'snot whatIa mtellingu!'\n");
      g->incorrect++;
      if(g->incorrect == 3){
        fprintf(stdout, "Vic(much more angrier): 'Ohh f*** offu idsiot xddd'\n\n");
        /*AQUI PETA message_array_destroy(g->m);*/
        free(g);
        free(answer);
        return LOOSE;
      }
      continue;
    }

    /*Rest case when the answer is correct*/
    fprintf(stdout, "Vic(cute): 'Ieees, in plan uknow xddd'\n");
    g->correct++;
  }

  fprintf(stdout, "Vic(happy): 'Yove underssthan %d of maisentencs:)'\n", g->correct);
  /*message_array_destroy(g->m); AQUI TAMBIEN PETA Y NO SE POR QUE COÑO*/
  free(g);
  free(answer);
  return WIN;
}
