/*DECRYPT VIC'S MESSAGE*/
/*All the int functions return -1 or ERR in case of memory error*/
#include "message.h"
#define WIN 10
#define LOOSE -10

struct _message{
  char *coded;           /*The coded message*/
  char *decoded;         /*The decoded message*/
  int num;               /*The number of the message*/
};

struct _game{
  Message *m[10];
  int correct, incorrect;
};


Message *message_ini(){
  Message *m = (Message*)malloc(sizeof(Message));
  if(!m) return NULL;

  m->coded = NULL;
  m->decoded = NULL;
  m->num = 0;
  return m;
}


void message_destroy(Message *m){
  if(!m) return;
  if(!m->coded){
    if(!m->decoded){
      free(m);
      return;
    }
    free(m->decoded);
    free(m);
    return;
  }

  if(!m->decoded){
    free(m->coded);
    free(m);
    return;
  }

  free(m->coded);
  free(m->decoded);
  free(m);
}


int message_set(Message **m, char *file){
  if(!f) return ERR;
  int i = 0, j;

  FILE *f;
  f = fopen(file,"r");
  if(!f) return ERR;

  while(!feof(f)){
    m[i] = message_ini();
    if(m[i] == NULL){
      for(j = i -1; j == 0; j--) message_destroy(m[i]);
      fclose(f);
      return ERR;
    }
    fscanf(f, "%d %s %s\n", m+i->num, m+i->coded, m+i->decoded);
    i++;
  }
  fclose(f);
  return 1;
}


/*It returns 0 if they are exactly the same and 1 if they're not*/
int message_compare(Message *m, char* answer){
  if(!m || !answer) return ERR;
  if(strcmp(m,answer) == 0) return 0;
  return 1;
}


int message_game(){
  int correct = 0, incorrect = 0, comp, i;
  Game *g = (Game*)malloc(sizeof(Game));
  if(!g) return ERR;

  if(message_set(g->m, "~/Decrypte Vic's message/Messages.txt") == ERR) return ERR;
  for(i = 0; i <= 10; i++){

  }

}
