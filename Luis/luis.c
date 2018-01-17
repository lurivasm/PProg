#include "interface.h"
#include "luis.h"
#include <time.h>
#include <termios.h>
#include <pthread.h>
struct termios initial;

int easy = 0;

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
        move ((Interface*)i,-mover);
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
		for (int j = 84; j > 3; j--){
			if (j == 4){
				pos = player_get_position(i);
				if (pos[0] > 7 && pos[0] < (8 + len)){
					free (pos);
					return 0;
				}
			}
			for (int k = 8; k < (8 + len); k++){
					if (j != 84){
							win_write_char_at(board,k,j+1,word[k-8]);
						}
					win_write_char_at(board,k,j,word[k-8]);
				}
			}
			return 1;
		}
		if (place == 0){
		for (int j = 84; j > 3; j--){
			if (j == 4){
				pos = player_get_position(i);
				if (pos[0] > (14 - len) && pos[0] < 15){
					free (pos);
					return 0;
				}
			}
			for (int k = 14; k > (14 - len); k--){
					if (j != 84){
							win_write_char_at(board,k,j+1,word[14-k]);
						}
					win_write_char_at(board,k,j,word[14-k]);
				}
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
		int sizeb[2],sizes[2],sizet[2];
		int cont = 0, fail = 0, flag = 0, len = 0, ran = 0;
		sc_rectangle* t, *s;

		srand(time(NULL));

		printf("\e[?25l");
		fflush(stdout);
		if (i == NULL) return -1;

		score = create_map("score",sizes);
		text = create_map("text",sizet);
		board = create_map("beginin.txt",sizeb);

		set_score(i,score,sizes[0],sizes[1]);
		draw_score(i,1);

		set_text(i,text,sizet[0],sizet[1]);
		draw_text(i,1);

		set_board(i,board,sizeb[0],sizeb[1]);
		draw_board(i,1);

		t = get_text(i);

		s = get_score(i);

	  win_write_line_at(t,4,4,"Press the space bar to continue");

		while(1){
		quit = _read_key();
		/*pressing q it exits*/
		if (quit == 'q')  return;
		/*if you press thedraw_board(i,1); space bar,you move foward*/
		if(quit == 32){
			int k;
			for(k = 0;k<sizeb[0];k++){
				free(board[k]);
			}
			free(board);
			break;
			}
		}
		win_write_line_at(t,4,4,"Javiti: I should go to cirel or I would fail");
		usleep(2000000);
		draw_text(i,1);

		win_write_line_at(t,4,4,"Jose: C'mon we are going to the resi");
		usleep(2000000);
		draw_text(i,1);

		win_write_line_at(t,4,4,"Santi: We are going to play table tenis and pool");
		usleep(2000000);
		draw_text(i,1);

		win_write_line_at(t,4,4,"Javiti: Pfff okay... But tomorrow we will go to Pprog");
		usleep(2000000);
		draw_text(i,1);

		win_write_line_at(t,4,4,"Jorge: Estaas...");
		usleep(2000000);
		draw_text(i,1);

		win_write_line_at(t,4,4,"Press the space bar to continue");

		win_write_line_at(s,3,6,"Try to skip all the classes");

		win_write_line_at(s,5,6,"If you go to three clases, you lose");

		win_write_line_at(s,7,6,"Good luck!");

		while(1){
		quit = _read_key();
		/*pressing q it exits*/
		if (quit == 'q')  return;
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

		win_write_line_at(s,4,6,"Score:");

		win_write_line_at(s,6,6,"Fail: 0");

		board = create_map("board",sizeb);

		set_board(i,board,sizeb[0],sizeb[1]);
		set_player(i,'J',4,11);

		draw_board(i,1);

		pthread_create(&pth,NULL, moving,(void*)i);

		while (cont < 20 && fail < 3){
			draw_board(i,1);
			ran = rand()%11;
			len = get_asignatura(ran,asignatura);
			if (len == -1) return -1;

			if (easy == 1) return 1;

			flag = words(asignatura,i,len);
			if (flag == 1) cont ++;
			if (flag == 0) fail ++;
		}
		int j;
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

		if (cont == 20) return 1;
		if (fail == 3) return 0;

}
