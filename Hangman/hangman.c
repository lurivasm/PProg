#include "hangman.h"


struct _hangman{
	int aciertos;
	int aciertos_palabras;
	int errores;
	int errores_palabras;
	char* palabras[30];
};



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

void current_errors(int i, FILE* out) {

    if (out==NULL) {
      return;
    }
     switch (i) {
         case 0 :
          fprintf(out,"\n\n");
          fprintf(out,"\n");
          fprintf(out,"  |\n");
          fprintf(out,"  |\n");
          fprintf(out,"  |\n");
          fprintf(out,"  |\n");
          fprintf(out,"  |\n");
          fprintf(out,"__|_________\n\n");
         break;
         case 1 :
          fprintf(out,"\n\n");
          fprintf(out,"  _______\n");
          fprintf(out,"  |/\n");
          fprintf(out,"  |\n");
          fprintf(out,"  |\n");
          fprintf(out,"  |\n");
          fprintf(out,"  |\n");
          fprintf(out,"__|_________\n\n");
         break;
         case 2 :
          fprintf(out,"\n\n");
          fprintf(out,"  _______\n");
          fprintf(out,"  |/   | \n");
          fprintf(out,"  |    O \n");
          fprintf(out,"  |    |\n");
          fprintf(out,"  |    |\n");
          fprintf(out,"  |\n");
          fprintf(out,"__|_________\n\n");
         break;
         case 3:
          fprintf(out,"\n\n");
          fprintf(out,"  _______\n");
          fprintf(out,"  |/   | \n");
          fprintf(out,"  |    O \n");
          fprintf(out,"  |   \\|\n");
          fprintf(out,"  |    | \n");
          fprintf(out,"  |\n");
          fprintf(out,"__|_________\n\n");
         break;
         case 4 :
          fprintf(out,"\n\n");
          fprintf(out,"  _______\n");
          fprintf(out,"  |/   | \n");
          fprintf(out,"  |    O \n");
          fprintf(out,"  |   \\|/\n");
          fprintf(out,"  |    | \n");
          fprintf(out,"  |\n");
          fprintf(out,"__|_________\n\n");
         break;
         case 5 :
          fprintf(out,"\n\n");
          fprintf(out,"  _______\n");
          fprintf(out,"  |/   | \n");
          fprintf(out,"  |    O \n");
          fprintf(out,"  |   \\|/\n");
          fprintf(out,"  |    | \n");
          fprintf(out,"  |   /\n");
          fprintf(out,"__|_________\n\n");
         break;
         case 6 :
				 fprintf(out,"\n\n");
				 fprintf(out,"  _______\n");
				 fprintf(out,"  |/   | \n");
				 fprintf(out,"  |    X \n");
				 fprintf(out,"  |   \\|/\n");
				 fprintf(out,"  |    | \n");
				 fprintf(out,"  |   / \\\n");
				 fprintf(out,"__|_________\n\n");
				break;

     }
    }

void print_current_word(char* cword, char* gword, FILE* out) {
  int i;

  if ((cword== NULL) || (gword==NULL) || (out==NULL)) {
    return;
  }
  for (i=0; i<strlen(gword) ; i++) {

    if (gword[i] == cword[i]) {

      fprintf(out, " %c ", toupper(cword[i]));
    }

    else if( gword[i] == ' ') {

        fprintf(out, "  ");

    }

    else {
      fprintf(out, " _ ");
    }


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

void showLogo(FILE* out) {

          if(out==NULL) {
            return;
          }

          fprintf(out,"--------------------------------------------\n");
          fprintf(out,"| #  #   #   #   #  #### #   #   #   #   # |\n");
          fprintf(out,"| #  #  # #  ##  # #     ## ##  # #  ##  # |\n");
          fprintf(out,"| #### ##### # # # #  ## # # # ##### # # # |\n");
          fprintf(out,"| #  # #   # #  ## #   # #   # #   # #  ## |\n");
          fprintf(out,"| #  # #   # #   #  ###  #   # #   # #   # |\n");
          fprintf(out,"--------------------------------------------\n\n");
    }

void hangman_play( hangman* hm, FILE* out, FILE* in) {
	char c;
	int a =0,aa, b=0, z=0,  d=0, y=0, k=0, l, i,t,s,  guessedLetter=0, length,*words,inf,max,cat_aux;
	char cat;
	int flag = 0;
	int j;
	char *currentWord, *guessWord, *wrongLetters;

  if ((hm==NULL) || (out == NULL) || (in==NULL)) return;



  words = (int*)malloc(sizeof(int) * 10);
  if (words==NULL) {
    return;
  }
	wrongLetters = (char*)malloc(6);


  showLogo(stdout);

  fprintf(out,
     "Welcome to the game Hangman!\n"
      "The objective in this game is to guess the word.\n"
      "You can enter lowercase or uppercase letters.\n"
      "You are allowed to enter just one letter at a time.\n"
      "You will loose if you have guessed 6 letters wrong.\n"
      "You pass the minigame if you guess 3 words correctly\n"
      "and you loose if you fail 2 words.\n"
      "Let´s start with the first word!\n");


	while (hm->errores_palabras < 2 && hm->aciertos_palabras < 3) {
		flag = 0;
		while(flag == 0){
			fprintf(out, "\n\nChoose a category for the next word (You can choose one category only twice during the game):\n\tHistorical Figures (press 1)\n\tFilms (press 2)\n\tCountries (press 3)\n\t");
			fscanf(in, "%c", &cat);
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
					b++;
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
					fprintf(out,"You have to enter either 1, 2 or 3\n");
			}
		}
	if ((a > 2) || (b > 2) || (d>2)) {
		while(cat == cat_aux) {
		fprintf(out, "\nYou can choose a category only twice. Try again:\n");
		fscanf(in, "%c", &cat);
		switch(cat) {
		case(49):
			inf = 0;
			max = 6;
			a++;
			break;
		case(50):
			inf = 7;
			max = 13;
			b++;
			break;
		case(51):
			inf = 14;
			max = 21;
			d++;
			break;
		/*case(4):
			inf = 22;
			max = 28;
			break;*/
		}
		}

	}
    hm->errores = 0;
		k=0;
    j= randomNumber(inf, max);
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
    /*fprintf(out, "\n%s\n", guessWord);*/
		for (s=0; s < length; s++) {
		if(guessWord[s] == ' ') {

        fprintf(out, "  ");

    }

    else {
      fprintf(out, " _ ");
    }
	}
		fprintf(out, "\n\nIntroduce a letter:\n");
		fprintf(out, "\n\n");
		fscanf(in, " %c", &c);
		 c = tolower(c);

    while ( (strcmp(currentWord, guessWord) != 0) && (hm->errores < 6) ) {
          guessedLetter =0;
      for (i = 0; i < length; i++) {
        if (guessWord[i] == c) {
          currentWord[i] = c;
          guessedLetter=1;
        }
      }

      if (guessedLetter == 0) {
        hm->errores++;
				wrongLetters[k] = c;
				k++;
        fprintf(out, "The letter was incorrect.\n");
				}
      else if (guessedLetter == 1) {
        guessedLetter = 0;
        fprintf(out, "The letter was correct.\n");
      }

			fprintf(out, "Letters you guessed wrong:");
			for (t=0; t < k; t++) {
				fprintf(out, "%c ", toupper(wrongLetters[t]));
			}
      current_errors(hm->errores, stdout);

      if ( (strcmp(currentWord, guessWord) != 0) && (hm->errores < 6) ) {
            print_current_word(currentWord, guessWord, out);
            fprintf(out,"\n\nEnter the letter(s) you want to guess:\n ");
            fscanf(in, " %c", &c);
						 c = tolower(c);
        }
		}

		if (hm->errores < 6) {
			if (strcmp(currentWord, guessWord) == 0) {
				fprintf(out, "Congratulations you have guessed the right word! Let´s go for the next one!\n");
				hm->aciertos_palabras++;
        fprintf(out,"-----------------------\n");
        fprintf(out,"--- Current Results ---\n");
        fprintf(out,"-----------------------\n");
        fprintf(out, "Words guessed correctly: %d\nWords guessed wrong: %d", hm->aciertos_palabras,hm->errores_palabras);
			}
			else {
				fprintf(out, "You have guessed the wrong word, better luck next time!\n");
				hm->errores_palabras++;
				for (l=0; l<length ; l++){
	 				guessWord[l] = toupper(guessWord[l]);
				}
				fprintf(out, "The word was: %s\n", guessWord);
        fprintf(out,"-----------------------\n");
        fprintf(out,"--- Current Results ---\n");
        fprintf(out,"-----------------------\n");
        fprintf(out, "Words guessed correctly: %d\nWords guessed wrong: %d\n", hm->aciertos_palabras,hm->errores_palabras);
			}
		}
		else if (hm->errores >= 6) {
			fprintf(out, "You have guessed the wrong word, better luck next time!\n");
			hm->errores_palabras++;
			for (l=0; l<length ; l++) {
				guessWord[l]=toupper(guessWord[l]);
			}
			fprintf(out, "The word was: %s\n", guessWord);
      fprintf(out,"-----------------------\n");
        fprintf(out,"--- Current Results ---\n");
        fprintf(out,"-----------------------\n");
        fprintf(out, "Words guessed correctly: %d\nWords guessed wrong: %d", hm->aciertos_palabras,hm->errores_palabras);
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

	}

if (hm->aciertos_palabras == 4) {
  fprintf (out, "\nCongratulations! You won the minigame!\n");
}

else if (hm->errores_palabras == 2) {
  fprintf(out, "\nSorry! You lost the minigame. Better luck next time\n");
}
free(words);
free(wrongLetters);

}
