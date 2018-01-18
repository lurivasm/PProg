#include "play.h"
#include "world.h"

struct termios initial;

void main(){
  World *w;
  Interface *i;

  _term_init();

  i=inter_create(33,114,0,0,0,86,22,0);
  w = create_world();
  play(w,i);
  tcsetattr(fileno(stdin), TCSANOW, &initial);	/*We now restore the settings we back-up'd
							so that the termial behaves normally when
							the program ends*/
}
