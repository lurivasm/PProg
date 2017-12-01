#include "interface.h"





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

Interface * inter_create(int rows,int columns,int r1,int c1){
	if (rows<=0||columns<=0) return NULL;
	Interface* i;
	i=(Interface*)malloc(sizeof(Interface));
	if (i==NULL) return NULL;
	i->r1 = r1;
	i->c1 = c1;
	i->rows=rows;
	i->columns=columns;
	i->board=win_new(1,1,rows,columns,BACKGROUND,FOREGROUND);
	i->score=win_new(1,84,rows,columns,BACKGROUND,FOREGROUND);
	i->player=' ';
	i->player_row=0;
	i->player_column=0;
	fprintf(stdout, "%c[2J", 27);
	return i;
};

void inter_delete(Interface*i){
	if (i==NULL) return ;
	if (i->board==NULL) {
		free(i);
		return;
	}
	if (i->score==NULL) {
		free(i);
		return;
	}
	win_delete(i->board);
	win_delete(i->score);
	free(i);
	return;
}

int set_player(Interface* i,char player,int row,int column){
	if (i==NULL) return 0;
	if (row<=0||column<=0) return 0;
	i->player=player;
	i->player_row=row;
	i->player_column=column;
	return 1;
}

int set_board(Interface* i,char **board,int row,int columns){
	if (board==NULL||row>i->rows||columns>i->columns) return 0;
	i->map=board;
	i->map_rows=row;
	i->map_columns=columns;
	return 1;
}

int draw_board(Interface* i, int clear){
	if (i==NULL) return 0;
	if (clear) win_cls(i->board);
	int j;
	for (j=i->r1;j<i->map_rows;j++){
		win_write_line_at(i->board,j,i->c1,i->map[j]);
	}
	win_write_char_at(i->board,i->player_row,i->player_column,i->player);
	return 1;
}

int draw_score(Interface* i, int clear){
	if (i==NULL) return 0;
	if (clear) win_cls(i->score);
	int j;
	for (j=i->r1;j<i->map_rows;j++){
		win_write_line_at(i->board,j,i->c1,i->map[j]);
	}
	win_write_char_at(i->board,i->player_row,i->player_column,i->player);
	return 1;
}

static int Dr[5] = {-1, 1, 0, 0, 0};
static int Dc[5] = {0, 0, 1, -1, 0};
int move(Interface *i,int direction){
	if (i==NULL||direction>4||direction<0) return -3;
	int r,c;
	r=i->player_row+Dr[direction];
	c=i->player_column+Dc[direction];
	if(r<0||c<0||r>=i->rows||c>=i->columns) return -2;
	if (i->map[r][c]!=' ') {
		return -1;
	}
	win_write_char_at(i->board,i->player_row,i->player_column,' ');
	i->player_column=c;
	i->player_row=r;
	win_write_char_at(i->board,i->player_row,i->player_column,i->player);
	return r<<8 +c;
}

int _read_key() {
  char choice;
  choice = fgetc(stdin);


  if (choice == 27 && fgetc(stdin) == '[') { /* The key is an arrow key */
    choice = fgetc(stdin);

    switch(choice) {
    case('A'):
      return -NORTH;
    case('B'):
      return -SOUTH;
    case('C'):
      return -EAST;
    case('D'):
      return -WEST;
    default:
      return -HERE;
    }
  }
  else
    return choice;
}

char **create_map(char *file,int *size){
	if (file==NULL) return 0;
	FILE *f;
	f=fopen(file,"r");
	if (f==NULL){
		printf("No existe el archivo\n");
		return 0;
	}
	char buf[1000];
	int rows = atoi(fgets(buf, 1000, f));
	int cols = atoi(strchr(buf, ' ')+1);

	char **map=(char**)malloc(sizeof(char*)*rows);
	for(int r=0;r<rows;r++){
		map[r]=(char*)malloc(cols+1);
		fgets(buf, 1000, f);
		int k=0;
		if (buf[strlen(buf)] == '\n')
			buf[strlen(buf)] = 0;
		for (;k<strlen(buf) && k<cols; k++)
			map[r][k] = buf[k];
		for (;k<cols; k++)
			map[r][k] = ' ';
		map[r][k] = 0;
	}

	fclose(f);
	size[0]=rows;
	size[1]=cols;
	return map;
}



sc_rectangle* get_board(Interface *i){
	if(!i) return NULL;
	return i->board;
}
