#include "player.h"

struct _player{
  int alcohol;
  char name[20];
};

Player* create_player(){
  Player* pl;
  int i;
  pl=(Player*)malloc(sizeof(Player));
  if (pl==NULL) return NULL;
  pl->alcohol=60;


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

 int get_alcohol(Player* pl){
   return pl->alcohol;
 }

 int is_dead(Player* pl){
   if (pl==NULL) return ERR;
   if (pl->alcohol==100) return -1;
   return 0;
 }
