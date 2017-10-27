 #include "mane.h"
 typedef struct Maze{
 	char map[100][35];
 	char delimiter;
 	char kill;
 };
/* The file contains: first row: delimiter kill\n; then it includes the map*/
 Maze * maze_ini(char* file){
 	FILE *f;
 	Maze* m;
 	char c;
 	int i=0,j=0;
 	if (file==NULL) return NULL;
 	m=(Maze*)malloc(sizeof(Maze));
 	if (m==NULL) return NULL;
 	f=fopen(file,"r");
 	if (f==NULL) return NULL;
 	fscanf(f,"%c %c\n",m->delimiter,m->kill);
 	while (!feof(f)){
 		fscanf(f,"%c",c);
 		if (c=='\n'){
 			i++;
 			j=0;
 			continue;
 		}
 		map[i][j]=c;
 		j++;
 	}
 	fclose(f);
 	return m;
 }
/* Returns the position char; '-1' if error, '0' if out of limits*/

 char position_char(int row, int column, Maze* m){
 	if (m==NULL) return '-1';
 	if (row>100 || row<-1) return '0';
 	if (column>35 || column<-1) return '0';
 	return map[row][column];
 }
/* Return 1 if kills you; 0 if not;-1 if err*/
 int kills_char(int row,int column, Maze* m){
 	char c;
 	if (m==NULL) return ERR;
 	c=position_char(row,column,m);
 	if (c=='-1') return ERR;
 	if (c==m->kill) return 1;
 	return 0;
 }
/* Return 1 if it is a delimiter you; 0 if not;-1 if err*/
 int delimiter_char (int row,int column,Maze *m){
 	char c;
 	if (m==NULL) return ERR;
 	c=position_char(row,column,m);
 	if (c=='-1') return ERR;
 	if (c==m->delimiter) return 1;
 	return 0;
 }