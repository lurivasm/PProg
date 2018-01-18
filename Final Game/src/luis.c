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
/*  Made by: Juan Velasco                       */
/************************************************/

#include "interface.h"
#include "luis.h"
#include <time.h>
#include <termios.h>
#include <pthread.h>

int easy = 0;

static int Dr[5] = {-1, 1, 0, 0, 0};
static int Dc[5] = {0, 0, 1, -1, 0};
void moving (void *i){
    int mover;

    while (1){
        mover = _read_key();
        fflush(stdout);
        if (mover == 'q'){
          easy = 1;
          pthread_exit (NULL);
          return;
        }
        if (mover == -EAST || mover == -WEST) continue;
        move (i,-mover);
        fflush(stdout);
    }
}

int words(char *word,Interface *i,int len){
    if (word == NULL || i == NULL) return -1;
		sc_rectangle *board;
		int place;
		int *pos;
		board	=	get_board(i);
		place = rand()%2;
    if (board == NULL) return -1;
		if (place == 1){
		for (int j = 83; j > 2; j--){
			if (j == 3){
				pos = player_get_position(i);
				if (pos[0] > 7 && pos[0] < (7 + len)){
					for (int k = 7; k < (7 + len); k++){
					   	win_write_char_at(board,k,j+1,' ');
						}
					free (pos);
					return 0;
				}
			}
			for (int k = 7; k < (7 + len); k++){
					if (j != 83){
							win_write_char_at(board,k,j+1,' ');
						}
					win_write_char_at(board,k,j,word[k-7]);
				}
				usleep(13000);
			}
			for (int k = 7; k < (7 + len); k++){
					win_write_char_at(board,k,3,' ');
				}
			return 1;
		}
		if (place == 0){
		for (int j = 83; j > 2; j--){
			if (j == 3){
				pos = player_get_position(i);
				if (pos[0] > (13 - len) && pos[0] < 13){
					for (int k = 13; k > (13 - len); k--){
						win_write_char_at(board,k,j+1,' ');
						}
					free (pos);
					return 0;
				}
			}
			for (int k = 13; k > (13 - len); k--){
					if (j != 83){
							win_write_char_at(board,k,j+1,' ');
						}
					win_write_char_at(board,k,j,word[13-k]);
				}
				usleep(13000);
			}
			for (int k = 13; k > (13 - len); k--){
					win_write_char_at(board,k,3,' ');
			}
			return 1;
		}
}

int get_asignatura(int num, char* asignatura){
	switch (num) {
		case 0:
			strcpy (asignatura,"Anal");
			return 4;
		case 1:
			strcpy (asignatura,"Cirel");
			return 5;
		case 2:
			strcpy (asignatura,"Edat");
			return 4;
		case 3:
			strcpy (asignatura,"Prog1");
			return 5;
		case 4:
			strcpy (asignatura,"Prog2");
			return 5;
		case 5:
			strcpy (asignatura,"Algeo");
			return 5;
		case 6:
			strcpy (asignatura,"Calc");
			return 4;
		case 7:
			strcpy (asignatura,"CyN");
			return 3;
		case 8:
			strcpy (asignatura,"Elec");
		  return 4;
		case 9:
			strcpy (asignatura,"Alg");
			return 3;
		case 10:
			strcpy (asignatura,"Lab");
			return 3;
		default:
			return -1;
	}
}


int play_luis (Interface *i){
    pthread_t pth;
		char** board;
		char** score;
		char** text;
		char asignatura[50];
		char p[50];
		int sizeb[2],sizes[2],sizet[2];
		int cont = 0, fail = 0, flag = 0, len = 0, ran = 0;
		int quit;
		sc_rectangle* t, *s;

		srand(time(NULL));

		printf("\e[?25l");
		fflush(stdout);
		if (i == NULL) return -1;

		board = create_map("begining.txt",sizeb);


		draw_score(i,1);


		draw_text(i,1);

		set_board(i,board,sizeb[0],sizeb[1]);
		draw_board(i,1);

		t = get_text(i);

		s = get_score(i);

	  win_write_line_at(t,4,4,"Press the space bar to continue");

		while(1){
		quit = _read_key();
		/*if you press thedraw_board(i,1); space bar,you move foward*/
		if(quit == 32){
			break;
			}
		}
		win_write_line_at(t,4,4,"Javiti: I should go to cirel or I would fail.");
		usleep(4000000);
		draw_text(i,1);

		win_write_line_at(t,4,4,"Jose: C'mon we are going to the resi.");
		usleep(4000000);
		draw_text(i,1);

		win_write_line_at(t,4,4,"Santi: We are going to play table tenis and pool,");
		usleep(4000000);
		draw_text(i,1);

		win_write_line_at(t,4,4,"Javiti: Pfff okay... But tomorrow we will go to Pprog.");
		usleep(4000000);
		draw_text(i,1);

		win_write_line_at(t,4,4,"Jorge: Estaas...");
		usleep(4000000);
		draw_text(i,1);

		win_write_line_at(t,4,4,"Press the space bar to continue");

		win_write_line_at(s,3,4,"Try to skip all");

		win_write_line_at(s,5,4,"the classes.");

		win_write_line_at(s,7,4,"If you go to three");

		win_write_line_at(s,9,4,"classes, you lose.");

		win_write_line_at(s,11,4,"Good luck!");

		while(1){
		quit = _read_key();
		/*pressing q it exits*/
		if (quit == 'q')  return 1;
		/*if you press the space bar,you move foward*/
		if(quit == 32){
			int k;
			for(k = 0;k<sizeb[0];k++){
				free(board[k]);
			}
			free(board);
			break;
			}
		}

		draw_text(i,1);
		draw_score(i,1);



		win_write_line_at(s,6,6,"Fail: 0");

		board = create_map("board",sizeb);

		set_board(i,board,sizeb[0],sizeb[1]);
		set_player(i,'J',11,3);

		draw_board(i,1);

		pthread_create(&pth,NULL, moving,(void*)(i));

		while (cont < 20 && fail < 3){
			ran = rand()%11;
			len = get_asignatura(ran,asignatura);
			if (len == -1) return -1;

			if (easy == 1) return 1;

			flag = words(asignatura,i,len);
			if (flag == 1) cont ++;
			if (flag == 0) fail ++;

			sprintf(p,"%d",fail);
			win_write_line_at(s,6,12,p);
		}
		int j;
		for(j = 0;j<sizeb[0];j++){
			free(board[j]);
		}

		pthread_cancel(pth);

		free(board);
		free(text);
		free(score);

		if (cont == 20) return 1;
		if (fail == 3) return 0;

}
