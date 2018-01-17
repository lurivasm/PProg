#include "world.h"


World* create_world(){
  World *w;
  int i;
  w = (World*)malloc(sizeof(World));

  w->p = create_player();
  for(i = 0;i < 8 ; i++) w->played[i] = 0;   /*Sets the list of played minigames with all 0(means you havent't played any mimigame yet*/)
  w->minigames = 0;  /*sets the number of minigames played to 0*/
  return w;
}

int read_played(World *w, int pos){  /*Returns 0 if the minigame pos wasn't palyed yet,1 if you have played it*/
  return w->played[pos];
}
void write_played(World *w, int pos){ /*Set the minigame pos as played,and increases the played minigames counter*/
  w->played[pos] = 1;
  w->minigames ++;
}

/*Returns the name of the station you're in. A station can appear more than once.Before you have played at least 4 minigames
 you can't get to the station 7(final station).FRom the 4 minigame you can get to the 7 station,and in the worst case,where you
 play all minigames(8),yo?ll finally get  to the 7 station*/
char* get_station(World *w){
  int aleat;
  char name[20];
  if(w->minigames < 4) aleat = rand()%7;
  if(w->minigames == 4) aleat = rand()%8;
  if(w->minigames == 5) aleat = 1 +rand()%7;
  if(w->minigames == 6) aleat = 3 + rand()%5;
  if(w->minigames == 7) aleat = 5 + rand()%3;
  if(w->minigames == 8) aleat = 7;

  switch (aleat) {
    case 0:
      sprintf(name,"TRES OLIVOS");
      return name;
    case 1:
      sprintf(name,"PLAZACA");
      return name;
    case 2:
      sprintf(name,"NUEVOS MINISTERIOS");
      return name;
    case 3:
      sprintf(name,"ALONSO MARTINEZ");
      return name;
    case 4:
      sprintf(name,"PLAZA HISPANIA");
      return name;
    case 5:
      sprintf(name,"LAGO");
      return name;
    case 6:
      sprintf(name,"PUERTA DEL SUR");
      return name;
    case 7:
      sprintf(name,"JOAQUÍN VILUMBRALES");
      return name;
  }
}


Player* get_player(World *w){
  return w->p;
}
