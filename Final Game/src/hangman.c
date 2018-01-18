/************************************************/
/*              PPROG VIDEOGAME                 */
/*         DREAM OF A JAVITI'S NIGHT            */
/*                                              */
/*  Members of the group:                       */
/*           - Javier Martínez                  */
/*           - Lucía Rivas                      */
/*           - Daniel Santo-Tomás               */
/*           - Juan Velasco                     */
/*                                              */
/*  Made by: Javier Martínez                    */
/************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <time.h>
#include <unistd.h>


#include <termios.h>
#include <pthread.h>
#include "interface.h"
#include "hangman.h"


struct _hangman{
	int aciertos;
	int aciertos_palabras;
	int errores;
	int errores_palabras;
	char* palabras[30];
};

struct termios initial;



int main_hangman(Interface *i) {
	hangman* hm;
	char** board;

	int sizeb[2],mode,quit,game,k;
	/*We create the maps for the board,score and text and set them on the interface*/
	board = create_map("hangman.txt",sizeb);



	set_board(i, board, sizeb[0], sizeb[1]);
	draw_board(i, 1);


	draw_score(i,1);


	draw_text(i,1);



	sc_rectangle* t;
 	t = get_text(i);
 	if(!t) return -1;


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
			for(k = 0; k < sizeb[0]; k++){
				free(board[k]);
			}
			free(board);
			break;
		}
	}

	/*we create the new map,and draw it in board*/
 	board = create_map("hangman_board.txt",sizeb);
	set_board(i, board, sizeb[0], sizeb[1]);
	draw_board(i, 1);
	draw_text(i, 1);

	hm= hangman_ini("hangman_test.txt");
	if(hm==NULL) {
		return -1;
	}

	game = hangman_play (hm, stdout, stdin, i);;

	if(game == 0){
		for(k = 0; k < sizeb[0]; k++){
			free(board[k]);
		}
		free(board);

		board = create_map("looser.txt",sizeb);
		set_board(i, board, sizeb[0], sizeb[1]);
		draw_board(i, 1);
		win_write_line_at(t,4,4,"Thanks for playing!");


		for(k = 0; k < sizeb[0]; k++){
			free(board[k]);
		}


		free(board);


		hangman_destroy(hm);
		return 0;

	}


	else {
	for(k = 0; k < sizeb[0]; k++){
		free(board[k]);
	}
	free(board);

	board = create_map("winner.txt",sizeb);
	set_board(i, board, sizeb[0], sizeb[1]);
	draw_board(i, 1);
	win_write_line_at(t,4,4,"Thanks for playing!");


	for(k = 0; k < sizeb[0]; k++){
		free(board[k]);
	}


	free(board);


	hangman_destroy(hm);
	return 1;

	}


}





hangman* hangman_ini(char* file) {
	hangman* hm;
	FILE* f;
	int i, j, k=0;
	hm= (hangman*)malloc(sizeof(hangman)*40);
	if (hm==NULL){
		return NULL;
	}
	hm->aciertos=0;
	hm->aciertos_palabras=0;
	hm->errores=0;
	hm->errores_palabras=0;

	for (i=0; i<=30; i++) {
		hm->palabras[i]=(char*)malloc(sizeof(char)*30);
		if (hm->palabras[i]==NULL){
			for (j=i; j>=0; j--) {
				free(hm->palabras[j]);
			}
			return NULL;
		}
	}

	f=fopen(file, "r");
	if (f==NULL) return NULL;
	i = 0;
	while (!feof(f)) {
			fgets(hm->palabras[i], 40, f);
			i++;
	}
	fclose(f);

	for ( ; k <=20 ; k++) {
		hm->palabras[k][strlen(hm->palabras[k]) -1] = '\0';
	}

	return hm;
}

void hangman_destroy(hangman* hm) {
	int i;
	if (hm==NULL) {
		return;
	}
	for (i=0; i<=30; i++) {
		free(hm->palabras[i]);
	}
	free(hm);
}

void current_errors(int i, sc_rectangle *b) { /*We draw the hangman depending on the number of mistakes in one word*/

     switch (i) {
         case 0 :
          win_write_line_at(b,10,33," ");
          win_write_line_at(b,11,33,"  |");
          win_write_line_at(b,12,33,"  |");
          win_write_line_at(b,13,33,"  |");
          win_write_line_at(b,14,33,"  |");
          win_write_line_at(b,15,33,"  |");
          win_write_line_at(b,16,33,"__|_________");
         break;
         case 1 :
          win_write_line_at(b,10,33,"  _______");
          win_write_line_at(b,11,33,"  |/");
          win_write_line_at(b,12,33,"  |");
          win_write_line_at(b,13,33,"  |");
          win_write_line_at(b,14,33,"  |");
          win_write_line_at(b,15,33,"  |");
          win_write_line_at(b,16,33,"__|_________");
         break;
         case 2 :
          win_write_line_at(b,10,33,"  _______");
          win_write_line_at(b,11,33,"  |/   | ");
          win_write_line_at(b,12,33,"  |    O ");
          win_write_line_at(b,13,33,"  |    |");
          win_write_line_at(b,14,33,"  |    |");
          win_write_line_at(b,15,33,"  |");
          win_write_line_at(b,16,33,"__|_________");
         break;
         case 3 :
          win_write_line_at(b,10,33,"  _______");
          win_write_line_at(b,11,33,"  |/   | ");
          win_write_line_at(b,12,33,"  |    O ");
          win_write_line_at(b,13,33,"  |   \\|");
          win_write_line_at(b,14,33,"  |    | ");
          win_write_line_at(b,15,33,"  |");
          win_write_line_at(b,16,33,"__|_________");
         break;
         case 4 :
          win_write_line_at(b,10,33,"  _______");
          win_write_line_at(b,11,33,"  |/   | ");
          win_write_line_at(b,12,33,"  |    O ");
          win_write_line_at(b,13,33,"  |   \\|/");
          win_write_line_at(b,14,33,"  |    | ");
          win_write_line_at(b,15,33,"  |");
          win_write_line_at(b,16,33,"__|_________");
         break;
         case 5 :
          win_write_line_at(b,10,33,"  _______");
          win_write_line_at(b,11,33,"  |/   | ");
          win_write_line_at(b,12,33,"  |    O ");
          win_write_line_at(b,13,33,"  |   \\|/");
          win_write_line_at(b,14,33,"  |    | ");
          win_write_line_at(b,15,33,"  |   /");
          win_write_line_at(b,16,33,"__|_________");
         break;
         case 6 :
				 win_write_line_at(b,10,33,"  _______");
				 win_write_line_at(b,11,33,"  |/   | ");
				 win_write_line_at(b,12,33,"  |    X ");
				 win_write_line_at(b,13,33,"  |   \\|/");
				 win_write_line_at(b,14,33,"  |    | ");
				 win_write_line_at(b,15,33,"  |   / \\");
				 win_write_line_at(b,16,33,"__|_________");
				break;

     }
    }

void print_current_word(char* cword, char* gword, FILE* out, sc_rectangle* b) { /*We print the current word with the correctly guessed words*/
  int i, p=5;

  if ((cword== NULL) || (gword==NULL) || (out==NULL)) {
    return;
  }
  for (i=0; i<strlen(gword) ; i++) {

    if (gword[i] == cword[i]) {

      win_write_char_at(b, 20,p , toupper(cword[i]));
    }

    else if( gword[i] == ' ') {

        win_write_line_at(b, 20, p, "  ");

    }

    else {
      win_write_line_at(b, 20, p, " _ ");
    }
		p = p+3;

    }

  }


char randomNumber(int min_number, int max_number) {
    srand(time(NULL));
    int g = min_number + (rand() % (max_number - min_number + 1));
    return g;
    }

int c_is_in_words(int *words, int a, int tamanio) {
	int i;

	if (words == NULL) {
		return -1;
	}

	for (i=0; i < tamanio; i++) {
		if (words[i] == a) {
			return 1;
		}
	}

	return 0;
}


int hangman_play( hangman* hm, FILE* out, FILE* in, Interface* ini) {
	char c, w[50], aciertos[3], errores[3];
	int a =0,aa, v=0, z=0,  d=0, y=0, k=0, l, i,q,n,p,  guessedLetter=0, length,*words,inf,max,cat_aux;
	char cat;
	int flag = 0;
	int j;
	char *currentWord, *guessWord, *wrongLetters;

  if ((hm==NULL) || (out == NULL) || (in==NULL)) return -1;



  words = (int*)malloc(sizeof(int) * 10);
  if (words==NULL) {
    return -1;
  }
	wrongLetters = (char*)malloc(6);

	sc_rectangle *t, *s, *b;

    t = get_text(ini);
    s = get_score(ini);
    b = get_board(ini);


    win_write_line_at(s, 4, 4, "Welcome to HANGMAN!");
    win_write_line_at(s, 6, 4," Guess the word!");
    win_write_line_at(s, 8, 4," 6 wrong letters = Loose");
    win_write_line_at(s, 10, 4," 3 correct words = Win");
    win_write_line_at(s, 12, 4," 2 wrong words = Fail");
    win_write_line_at(s, 14, 4," Let´s start!");




	while (hm->errores_palabras < 2 && hm->aciertos_palabras < 3) {
		flag = 0;
		draw_text(ini,1);
		while(flag == 0){
			win_write_line_at(t,4,4, "Choose a category for the next word:");
			win_write_line_at(t,5,8, "Historical Figures (press 1)");
			win_write_line_at(t,6,8, "Films (press 2 )");
			win_write_line_at(t,7,8, "Countries (press 3)");
			tcsetattr(fileno(stdin), TCSANOW, &initial);
			fscanf(in, " %c", &cat);
			_term_init();
			cat_aux = cat;
			switch(cat) {
				case(49):
					inf = 0;
					max = 6;
					a++;
					flag = 1;
					break;
				case(50):
					inf = 7;
					max = 13;
					v++;
					flag = 1;
					break;
				case(51):
					inf = 14;
					max = 20;
					d++;
					flag = 1;
					break;
				/*case(4):
					inf = 22;
					max = 28;
					break;*/
				default:
					win_write_line_at(t,8,4,"You have to enter either 1, 2 or 3");
			}
		}
    hm->errores = 0;
		k=0;
    j= randomNumber(inf, max); /*We choose a random word (which can not be repeated)*/
		words[z]=j;

		if (z>0) {
			while (c_is_in_words(words, j, z) == 1) {
				j= randomNumber(inf, max);
				words[z]=j;
			}
		}

    length = strlen(hm->palabras[j]);

		currentWord=(char*)malloc( length +1);
		for(aa = 0; aa < length; aa++)
			currentWord[aa] = ' ';
		currentWord[length] = '\0';

		guessWord=(char*)malloc( length +1);
		strcpy(guessWord, hm->palabras[j]);

		y=0;
		draw_score(ini, 1);
		sprintf(aciertos, "%d", hm->aciertos_palabras);
		sprintf(errores, "%d", hm->errores_palabras);
		win_write_line_at(s,20,4,"-----------------------");
		win_write_line_at(s,22,4,"--- Current Results ---");
		win_write_line_at(s,24,4,"-----------------------");
		win_write_line_at(s, 26, 4, "Words guessed correctly:");
		win_write_line_at(s,26,28, aciertos);
		win_write_line_at(s, 28, 4, "Words guessed wrong: ");
		win_write_line_at(s, 28, 24,errores);

		p=5;

		for (n=0; n < length; n++) {
			if(guessWord[n] == ' ') {

        win_write_line_at(b,20,p, "   ");

    	}
			else {
      	win_write_line_at(b,20,p, " _ ");
    	}
		p=p+3;
	}
		win_write_line_at(b, 20, 4, w);
		draw_text(ini,1);
		win_write_line_at(t,6,4, "Introduce a letter: ");
		tcsetattr(fileno(stdin), TCSANOW, &initial);
		fscanf(stdin, " %c", &c);
		_term_init();
		 c = tolower(c);
		 win_write_char_at(t, 8, 4, c);


    while ( (strcmp(currentWord, guessWord) != 0) && (hm->errores < 6) ) {
          guessedLetter =0;
      for (i = 0; i < length; i++) { /*We make sure if the introduced letter is in the word or not*/
        if (guessWord[i] == c) {
          currentWord[i] = c;
          guessedLetter=1;
        }
      }

      if (guessedLetter == 0) {
        hm->errores++;
				wrongLetters[k] = c;
				k++;
				draw_text(ini,1);
        win_write_line_at(t,4,4, "The letter was incorrect.");
				}
      else if (guessedLetter == 1) {
        guessedLetter = 0;
				draw_text(ini,1);
        win_write_line_at(t,4,4, "The letter was correct.");
      }
			draw_score(ini,1);
			win_write_line_at(s,20,4,"-----------------------");
			win_write_line_at(s,22,4,"--- Current Results ---");
			win_write_line_at(s,24,4,"-----------------------");
			win_write_line_at(s, 26, 4, "Words guessed correctly:");
			win_write_line_at(s,26,28, aciertos);
			win_write_line_at(s, 28, 4, "Words guessed wrong: ");
			win_write_line_at(s, 28, 24,errores);
			win_write_line_at(s,4,4, "Letters guessed wrong:");
			p=4;
			for (q=0; q < k; q++) {
				win_write_char_at(s, 6,p, toupper(wrongLetters[q])); /*We print the letters guessed wrong*/
				p=p+2;
			}
			draw_board(ini,1);
      current_errors(hm->errores, b);

      if ( (strcmp(currentWord, guessWord) != 0) && (hm->errores < 6) ) {
            print_current_word(currentWord, guessWord, out, b);
            win_write_line_at(t,6,4,"Enter the letter(s) you want to guess: ");
						tcsetattr(fileno(stdin), TCSANOW, &initial);
            fscanf(in, " %c", &c);
						_term_init();
						 c = tolower(c);
        }
		}
		draw_score(ini,1);

		if (hm->errores < 6) {
			if (strcmp(currentWord, guessWord) == 0) {
				hm->aciertos_palabras++;
				sprintf(aciertos, "%d", hm->aciertos_palabras);
				sprintf(errores, "%d", hm->errores_palabras);
				win_write_line_at(s,11,4, "Congratulations!");
				win_write_line_at(s,12,4, "The word was right!");
				win_write_line_at(s,20,4,"-----------------------");
				win_write_line_at(s,22,4,"--- Current Results ---");
				win_write_line_at(s,24,4,"-----------------------");
				win_write_line_at(s, 26, 4, "Words guessed correctly:");
				win_write_line_at(s,26,28, aciertos);
				win_write_line_at(s, 28, 4, "Words guessed wrong: ");
				win_write_line_at(s, 28, 24,errores);
			}
			else {
				win_write_line_at(s, 8, 4, "The word was wrong!");
				win_write_line_at(s, 9, 4, "Better luck next time!");
				hm->errores_palabras++;
				sprintf(aciertos, "%d", hm->aciertos_palabras);
				sprintf(errores, "%d", hm->errores_palabras);
				for (l=0; l<length ; l++){
	 				guessWord[l] = toupper(guessWord[l]);
				}
				win_write_line_at(s,11,4, "The word was: ");
				win_write_line_at(s,12,4,guessWord);
				win_write_line_at(s,20,4,"-----------------------");
				win_write_line_at(s,22,4,"--- Current Results ---");
				win_write_line_at(s,24,4,"-----------------------");
				win_write_line_at(s, 26, 4, "Words guessed correctly:");
				win_write_line_at(s,26,28, aciertos);
				win_write_line_at(s, 28, 4, "Words guessed wrong: ");
				win_write_line_at(s, 28, 24,errores);
			}
		}
		else if (hm->errores >= 6) {
			win_write_line_at(s, 8, 4, "The word was wrong!");
			win_write_line_at(s, 9, 4, "Better luck next time!");
			hm->errores_palabras++;
			sprintf(aciertos, "%d", hm->aciertos_palabras);
			sprintf(errores, "%d", hm->errores_palabras);
			for (l=0; l<length ; l++) {
				guessWord[l]=toupper(guessWord[l]);
			}
			win_write_line_at(s,11,4, "The word was: ");
			win_write_line_at(s,12,4,guessWord);
			win_write_line_at(s,20,4,"-----------------------");
			win_write_line_at(s,22,4,"--- Current Results ---");
			win_write_line_at(s,24,4,"-----------------------");
			win_write_line_at(s, 26, 4, "Words guessed correctly:");
			win_write_line_at(s,26,28, aciertos);
			win_write_line_at(s, 28, 4, "Words guessed wrong: ");
			win_write_line_at(s, 28, 24,errores);
		}
		for (l=0; l<=length; l++) {
			currentWord[l] = '\0';
			guessWord[l] = '\0';
		}
		for (l=0; l<k; l++) {
			wrongLetters[l] = '\0';
		}

		free(currentWord);
		free(guessWord);
		z++;
		draw_board(ini,1);

	}

if (hm->aciertos_palabras == 4) {
	draw_score(ini,1);
	win_write_line_at(s,11,4,"-----------------------");
	win_write_line_at(s,13,4,"--- Final Results ---");
	win_write_line_at(s,15,4,"-----------------------");
	win_write_line_at(s, 17, 4, "Words guessed correctly:");
	win_write_line_at(s,17,28, aciertos);
	win_write_line_at(s, 19, 4, "Words guessed wrong: ");
	win_write_line_at(s, 19, 24,errores);
  return 1;
}

else if (hm->errores_palabras == 2) {
	draw_score(ini,1);
	win_write_line_at(s,11,4,"-----------------------");
	win_write_line_at(s,13,4,"--- Final Results ---");
	win_write_line_at(s,15,4,"-----------------------");
	win_write_line_at(s, 17, 4, "Words guessed correctly:");
	win_write_line_at(s,17,28, aciertos);
	win_write_line_at(s, 19, 4, "Words guessed wrong: ");
	win_write_line_at(s, 19, 24,errores);
  return 0;
}
free(words);
free(wrongLetters);

}
