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

struct termios initial;



void main(){
	Interface* i1,i2,i3;
	FILE *f;
	int quit;
	int j=0;
	char** map;
	int size[2];



	map = create_map("portada",size);
	i1=inter_create(32,112,0,0);
	set_board(i1,map,size[0],size[1]);
	draw_board(i1,1);
	_term_init();

	/*sc_rectangle* b1;
 	b1 = get_board(i1);
 	if(!b1) return;

	win_write_line_at(b1,15,2,"Press the space");
	win_write_line_at(b1,16,2,"bar to continue");


	printf("\e[?25l");
  fflush(stdout); */

	while(1){
	quit=_read_key();

	if (quit == 'q') {
		inter_delete(i1);
    tcsetattr(fileno(stdin), TCSANOW, &initial);	/*We now restore the settings we back-up'd
							  so that the termial behaves normally when
							  the program ends */
    return;
  }
	if(quit == 32){
		int k;
		for(k = 0;k<size[0];k++){
			free(map[k]);
		}
		free(map);
		break;
	}
	}

	map = create_map("sala",size);
	set_board(i1,map,size[0],size[1]);
	draw_board(i1,1);




	while(1){
	quit=_read_key();

	if (quit == 'q') {
		inter_delete(i1);
    tcsetattr(fileno(stdin), TCSANOW, &initial);
    return;
  }

 }


	tcsetattr(fileno(stdin), TCSANOW, &initial);
	return;
}
