/*DECRYPT VIC'S MESSAGE*/
/*All the int functions return -1 or ERR in case of memory error*/
#include "message.h"

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


void message_array_destroy(Message **m){
  if(!m) return;
  int i;

  for(i = 0; i < 10; i++) message_destroy(m[i]);
  free(m);
}


int message_set(Message **m, char *file){
  if(!file) return ERR;
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
    fscanf(f, "%d %s %s\n", m[i]->num, m[i]->coded, m[i]->decoded);
    i++;
  }
  fclose(f);
  return 1;
}


/*It returns 0 if they are exactly the same and 1 if they're not*/
int message_compare(Message *m, char* answer){
  if(!m || !answer) return ERR;
   return (strcmp(m->decoded, answer) == 0) ? 0 : 1;
}


Game *game_ini(){
  Game *g;
  g = (Game*)malloc(sizeof(Game));
  if(!g) return NULL;

  if(message_set(g->m, "~/Decrypte Vic's message/Messages.txt") == ERR) return NULL;
  g->correct = 0;
  g->incorrect = 0;
  return g;
}


int message_game(){
  int comp, i;
  char *answer;
  Game *g;

  answer = (char*)malloc(sizeof(char)+1);
  if(!answer) return ERR;

  g = game_ini();
  if(!g) {
    free(answer);
    return ERR;
  }


  for(i = 0; i < 10; i++){
    fprint(stdout, "\nVic: %s\nYou: ", g->m[i]->coded);
    fscanf(stdin, "%s\n", answer);

    comp = message_compare(g->m[i], answer);

    /*Case of error*/
    if(comp == ERR) {
      message_array_free(g->m);
      free(g);
      free(answer);
      return ERR;
    }

    /*The answer is incorrect*/
    if(comp == 1){
      fprintf(stdout, "Vic(angry): 'That 'snot whatIa mtellingu!'\n");
      g->incorrect++;
      if(g->incorrect == 3){
        fprintf(stdout, "Vic(much more angrier): 'Ohh f*** offu idsiot\n\n");
        message_array_free(g->m);
        free(g);
        free(answer);
        return LOOSE;
      }
      continue;
    }

    /*Rest case when the answer is correct*/
    fprintf(stdout, "Vic(cute): 'Ieees, in plan roll uknow'\n");
    g->correct++;
  }

  fprintf(stdout, "Vic(happy): 'Yove underssthan %d of maisentencs:)'\n", g->correct);
  message_array_free(g->m);
  free(g);
  free(answer);
  return WIN;
}
