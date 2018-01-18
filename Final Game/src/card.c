/************************************************/
/*              PPROG VIDEOGAME                 */
/*         DREAM OF A JAVITI'S NIGHT            */
/*                                              */
/*  Members of the group:                       */
/*           - Javier Martínez                  */
/*           - Lucía Rivas                      */
/*           - Daniel Santo-Tomás               */
/*           - Juan Velasco                     */
/*                                              */
/*  Made by: Daniel Santo-Tomás                 */
/************************************************/
#include "card.h"

struct _card {
  char* name;
  char* suit;
  int value;
};

Card* create_card(){
  Card* c;
  c = (Card*)malloc(sizeof(Card));
  if(!c) return NULL;
  c->value = -1;    /*To recoginse when a card has been created but has no information in it yet*/
  return c;
}

void delete_card(Card *c){
  free(c->name);
  free(c->suit);
  free(c);
  return;
  }

Card* set_card(Card* c,char* name,char* suit,int value){
  if(!c || !name || !suit || value <= 0) return NULL;

  (c->name)=(char*)malloc(sizeof(char)*(strlen(name)+1));
  if(!(c->name)) return NULL;

  (c->suit)=(char*)malloc(sizeof(char)*(strlen(suit)+1));
  if(!(c->suit)) return NULL;

  strcpy(c->name,name);
  strcpy(c->suit,suit);
  c->value = value;

  return c;
}

char* card_get_name(Card* c){
  if(!c) return NULL;
  return c->name;
}

char* card_get_suit(Card* c){
  if(!c) return NULL;
  return c->suit;
}

int card_get_value(Card* c){
  if(!c) return -1;
  return c->value;
}

void print_card(Card *c,FILE *f){
  if(!c) return;
  if(c->value == 1){
    fprintf(f,"%s of %s , 1 point or 11 points\n",c->name ,c->suit);
    return;
  }
  fprintf(f,"%s of %s , %d points\n",c->name ,c->suit ,c->value);
  return;
}

Card* card_copy(Card *c1, Card *c2){
  Card *caux;
  if(!c1) return NULL;
  if(!c2) return NULL;
  if(c1->value ==-1){
    c1 = set_card(c1,c2->name,c2->suit,c2->value);
    return c1;
  }
  delete_card(c1);
  caux = create_card();
  caux = set_card(caux,c2->name,c2->suit,c2->value);
  return caux;
}
