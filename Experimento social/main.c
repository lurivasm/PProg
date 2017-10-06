#include "rectangles.h"

int main(){
	sc_rectangle *r;
	FILE *f;
	char p;
	int fila,columna;
	r=win_new(0, 0, 9, 40, 40, 36);
	win_cls(r);
	f=fopen("prueba.txt","r");
	columna=0;
	fila=0;
	while (!feof(f)){
		fscanf(f,"%c",&p);
		if (p=='\n'){
			fila++;
			columna=0;
		};
		win_write_char_at(r,fila,columna,p);
		columna++;
	}
	printf("\n");
	fclose(f);
	win_delete(r);
}