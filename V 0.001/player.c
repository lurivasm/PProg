#include "player.h"

struct _player{
  int alcohol;
  int inventory[10];
  int state;
};

Player* create_player(){
  Player* pl;
  int i;
  pl=(Player*)malloc(sizeof(Player));
  if (pl==NULL) return NULL;
  pl->alcohol=0;
  pl->state=0;
  for (i=0;i<10;i++){
    pl->inventory[i]=-1;
  }
  return pl;
}

  void delete_player(Player* pl){
   free(pl);
 }

 int modify_alcohol(Player* pl,int mod){
   if (pl==NULL||mod>100||mod<-100) return ERR;
   pl->alcohol=pl->alcohol+mod;
   return OK;
 }

 int is_dead(Player* pl){
   if (pl==NULL) return ERR;
   if (pl->alcohol==100) return -1;
   return 0;
 }

 int change_state(Player* pl,int modifier){
   if (pl==NULL) return ERR;
   pl->state=modifier;
   return OK;
 }
