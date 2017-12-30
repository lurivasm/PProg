#include "mane.h"

void main(){
	Interface *i;
	i=inter_create(33,114,0,0,0,86,22,0);
	printf("hola hola hola\n"  );
	play_mane(i);
	inter_delete(i);
	return;
}
