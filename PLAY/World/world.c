#include "world.h"


World* create_world(){
  World *w;
  w = (World*)malloc(sizeof(World));

  w->i = inter_create(33,114,0,0,0,86,22,0);
  w->p = create_player();

  return w;
}

Interface* get_interface(World *w){
  return w->i;
}

Player* get_player(World *w){
  return w->p;
}
