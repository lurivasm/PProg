#include "play.h"
#include "world.h"



void main(){
  World *w;
  Interface *i;



  i=inter_create(33,114,0,0,0,86,22,0);
  w = create_world();
  play(w,i);
  
}
