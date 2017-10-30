#include "deck.h"
#include <time.h>

struct _deck{
  Card *cards[52];
};


Deck* create_deck(){
  Deck *d;
  int i;
  d = (Deck*)malloc(sizeof(Deck));
  for(i=0;i<52;i++){
    d->cards[i] = create_card();
    if(!(d->cards[i])) return NULL;
  }
  return d;
}


void delete_deck(Deck *d){
  int i;
  for(i=0;i<52;i++){
    delete_card(d->cards[i]);
  }
  free(d);
}


Deck* set_deck(Deck *d){
  if(!d) return NULL;
  char suits[4][10] = {"Spades","Clubs","Hearts","Diamonds"};
  char card_names[13][10] = {"Ace","Two","Three","Four","Five","Six","Seven","Eight","Nine","Ten","Jack","King","Queen"};

  int i,j,k;
  k = 0;

  for(i=0;i<4;i++){
    for(j=0;j<13;j++){
      if(j>=10){
        d->cards[k] = set_card(d->cards[k],card_names[j],suits[i],10);
        k++;
        continue;
      }
      d->cards[k] = set_card(d->cards[k],card_names[j],suits[i],(j+1));
      k++;
    }
  }
  return d;
}

Card* deck_get_card(Deck *d,int key){
  if(!d || key<0) return NULL;
  return d->cards[key];
}

Deck* shuffle(Deck *d){
  if(!d) return NULL;
  int i,aleat;
  Card *aux;
  aux = create_card();
  srand(time(NULL));

  for(i = 0;i < 52;i++){
    srand(rand());
    aleat = rand()%52;
    while(aleat == i) aleat = rand()%52;
    aux = card_copy(aux,d->cards[i]);
    d->cards[i]=card_copy(d->cards[i],d->cards[aleat]);
    d->cards[aleat]= card_copy(d->cards[aleat],aux);
  }
  delete_card(aux);
    return d;
}
