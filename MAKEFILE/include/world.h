#ifndef WORLD_H
#define WORLD_H


#include "player.h"
#include "interface.h"

typedef struct{
  int played[8];
  int minigames;
  Player* p;
}World;

World* create_world();

int read_played(World *w, int pos);
void write_played(World *w, int pos); /*Set the minigame pos as played,and increases the played minigames counter(w->minigames) */

char* get_station(World *w);
int minigames(World* w); /* Returns the minigames played*/

Player* get_player(World *w);



void save(World *w,int num);
void load(World* w,int num);



#endif
