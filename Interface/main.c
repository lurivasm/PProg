
#include <stdio.h>
#include <stdlib.h>    
#include "rec.h"

void main(){
	rectangle* r;
	r=rec_ini(0,0,15,15,1,1,45,35);
	win_clr(r);
	rec_del(r);
	return;
}