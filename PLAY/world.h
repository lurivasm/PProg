#ifndef WORLD_H
#define WORLD_H

#include "interface.h"
#include "player.h"

typedef struct{
  int played[8];
  int minigames;
  Player* p;
}World;

World* create_world();

int read_played(World *w, int pos);
int write_played(World *w, int pos); /*Set the minigame pos as played,and increases the played minigames counter(w->minigames) */

char* get_station(World *w);


Player* get_player(World *w);


#endif
