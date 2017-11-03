#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <memory.h>
#include "rec.h"

int move_to (rectangle* sr,int r,int c){
	if (r<0 || c<0) return ERR;
	if (r>=sr->num_r|| c>=sr->num_c) return ERR;
	r+=(sr->r_ini+1);
	c+=(sr->c_ini+1);
	printf("%c[%d;%dH", 27, r, c);
    return OK;
};

rectangle * rec_ini(int c_ini, int r_ini, int num_c, int num_r, int crs_r, int crs_c,int bg_colour,int fg_colour){
	rectangle * r;
	r=(rectangle*)malloc(sizeof(rectangle));
	if (r==NULL) return NULL;
	r->c_ini=c_ini;
	r->r_ini=r_ini;
	r->num_c=num_c,
	r->num_r=num_r;
	r->crs_c=crs_c;
	r->crs_r=crs_r;
	r->bg_colour=bg_colour;
	r->fg_colour=fg_colour;
	return r;
};

void rec_del(rectangle* r){
	if (r==NULL) return;
	free(r);
	return;
}

void win_clr (rectangle* sr){
	char *buf;
	int i;
	if (sr==NULL) return;
	buf = (char *) malloc((sr->num_c + 1) * sizeof (char));
	memset(buf, ' ', sr->num_c);
	buf[sr->num_c] = 0;
	printf("%c[%d;%dm", 27, sr->bg_colour, sr->fg_colour);
	for (i = sr->r_ini; i < sr->r_ini + sr->num_r; i++) {
        move_to(sr, i - sr->r_ini, 0);
        printf("%s", buf);
    }
    fflush(stdout);
    free(buf);
    return;
};

int win_bg (rectangle* r, int col){
	if (col<40 || col>49) return ERR;
	if (r==NULL) return ERR;
	r->bg_colour=col;
	return OK;
}

int win_fg (rectangle* r, int col){
	if (r==NULL) return ERR;
	if (col<30 || col>39) return ERR;
	r->fg_colour=col;
	return OK;
}

int win_write_line (rectangle* sr,int r,int c,char* str){
	char *nl_p;
	char save, av_space, ret;
	if (sr==NULL) return ERR;
	if (r>=sr->num_r||r>=sr->num_c) return ERR;
	nl_p = strchr(str, '\n');
    if (nl_p) *nl_p = 0;
    av_space = sr->num_c - c;
    save = -1;
    if (strlen(str) > av_space) {
        save = str[av_space - 1];
        str[av_space - 1] = 0;
    }
    printf("%c[%d;%dm", 27, sr->bg_colour, sr->fg_colour);
    move_to(sr,r,c);
    printf("%s", str);
    fflush(stdout);
    if (save > 0) {
        str[av_space - 1] = save;
        ret = av_space;
    } else
        ret = strlen(str);
    if (nl_p) *nl_p = '\n';
    return OK;
}

int win_write_char(rectangle* sr,int r,int c,char ch){
	if (sr==NULL) return ERR;
	if (r>=sr->num_r||c>=sr->num_c) return ERR;
	move_to(sr,r,c);
	printf("%c", ch);
    fflush(stdout);
    return OK;
}