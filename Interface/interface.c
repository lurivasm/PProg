#include "interface.h"


Interface * inter_create(int rows,int columns){
	if (rows<=0||columns<=0) return NULL;
	Interface* i;
	i=(Interface*)malloc(sizeof(Interface));
	if (i==NULL) return NULL;
	i->rows=rows;
	i->columns=columns;
	i->board=win_new(1,1,rows,columns,BACKGROUND,FOREGROUND);
	i->player='0';
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
	win_delete(i->board);
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
	for (j=0;j<i->map_rows;j++){
		win_write_line_at(i->board,j,0,i->map[j]);
	}
	win_write_char_at(i->board,i->player_row,i->player_column,i->player);
	return 0;
}

static int Dr[5] = {-1, 1, 0, 0, 0};
static int Dc[5] = {0, 0, 1, -1, 0}; 
int move(Interface *i,int direction){
	if (i==NULL||direction>4||direction<0) return -3;
	int r,c;
	r=i->player_row+Dr[direction];
	c=i->player_column+Dc[direction];
	if(r<0||c<0||r>=i->rows||c>=i->columns) return -2;
	if (i->map[r][c]!=' ') return -1;
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


