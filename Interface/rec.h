#ifndef REC_H
#define REC_H

#include <stdio.h>
#include <stdlib.h>    
  
#define ERR -1
#define OK (!(ERR)) 

typedef struct {
	int c_ini;
	int r_ini;
	int num_c;
	int num_r;
	int crs_r; //Cursor postiion (row)
	int crs_c; //Curson osition (column)
	int bg_colour;
	int fg_colour;
}rectangle;

rectangle * rec_ini(int c_ini, int r_ini, int num_c, int num_r, int crs_r, int crs_c,int bg_colour,int fg_colour);

void rec_del(rectangle* r);

void win_clr (rectangle* r);

int win_bg (rectangle* r, int col);

int win_fg (rectangle* r, int col);

int win_write_line (rectangle* sr,int r,int c,char* str);

int win_write_char(rectangle* sc,int r,int c,char ch);

#endif