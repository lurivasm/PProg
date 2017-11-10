#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interface.h"

void main(){
	Interface* i;
	FILE *f;
	int j=0;
	char** map;
	f=fopen("prueba","r");
	if (f==NULL){
		printf("falla lectura\n");
		return;
	}
	map=(char**)malloc(sizeof(char*)*11);
	for(j=0;j<11;j++){
		map[j]=(char*)malloc(sizeof(char)*66);
	}
	
	j=0;
	while(!feof(f)){
		fscanf(f,"%s\n",map[j]);
		j++;
	}

	fclose(f);

	i=inter_create(11,66);
	set_player(i,'c',3,33);
	set_board(i,map,11,66);
	draw_board(i,1);
	move (i,NORTH);
	fflush(stdout);
	inter_delete(i);
	return;
}