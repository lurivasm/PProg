/*DECRYPT VIC'S MESSAGE*/
/*All the int functions return -1 or ERR in case of memory error*/
#include "message.h"

struct _message{
  char *coded;           /*The coded message*/
  char *decoded;         /*The decoded message*/
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
  char *aux;
  FILE *f;

  f = fopen(file,"r");
  if(!f) return ERR;

  aux = (char*)malloc(sizeof(char)*500);
  if(!aux){
    fclose(f);
    return ERR;
  }

  while(!feof(f) && i < 10){
    m[i] = message_ini();
    if(m[i] == NULL){
      for(j = i -1; j == 0; j--) message_destroy(m[i]);
      fclose(f);
      return ERR;
    }
    fgets(aux, 500, f);

    m[i]->coded = strtok(aux, "/");
    if(!m[i]->coded){
      free(aux);
      fclose(f);
      return ERR;
    }

    m[i]->decoded = strtok(NULL, "/");
    if(!m[i]->decoded){
      free(aux);
      fclose(f);
      return ERR;
    }
    i++;
  }
  free(aux);
  fclose(f);
  return 1;
}


/*It returns 0 if they are exactly the same and 1 if they're not*/
int message_compare(Message *m, char* answer){
  if(!m || !answer) return ERR;
   return (strcmp(m->decoded, answer) == 0) ? 0 : 1;
}


Game *game_ini(char *file){
  if(!file) return NULL;

  Game *g;
  g = (Game*)malloc(sizeof(Game));
  if(!g) return NULL;

  if(message_set(g->m, file) == ERR) return NULL;
  g->correct = 0;
  g->incorrect = 0;

  return g;
}


int message_game(char *file){
  if(!file) return ERR;

  int comp, i;
  char *answer;
  Game *g;

  answer = (char*)malloc(sizeof(char)*200);
  if(!answer) return ERR;

  g = game_ini(file);
  if(!g) {
    free(answer);
    return ERR;
  }

  for(i = 0; i < 10; i++){
    fprintf(stdout, "%s\n", g->m[i]->decoded);
    fprintf(stdout, "\nVic: %s\nYou: ", g->m[i]->coded);
    fgets(answer, 100, stdin);

    comp = message_compare(g->m[i], answer);

    /*Case of error*/
    if(comp == ERR) {
      message_array_destroy(g->m);
      free(g);
      free(answer);
      return ERR;
    }

    /*The answer is incorrect*/
    if(comp == 1){
      fprintf(stdout, "Vic(angry): 'That 'snot whatIa mtellingu!'\n");
      g->incorrect++;
      if(g->incorrect == 3){
        fprintf(stdout, "Vic(much more angrier): 'Ohh f*** offu idsiot xddd'\n\n");
        /*AQUI PETA message_array_destroy(g->m);*/
        free(g);
        free(answer);
        return LOOSE;
      }
      continue;
    }

    /*Rest case when the answer is correct*/
    fprintf(stdout, "Vic(cute): 'Ieees, in plan uknow xddd'\n");
    g->correct++;
  }

  fprintf(stdout, "Vic(happy): 'Yove underssthan %d of maisentencs:)'\n", g->correct);
  message_array_destroy(g->m);
  free(g);
  free(answer);
  return WIN;
}
