#include "deck.h"

struct _deck{
  Card *cards[52]
};


Deck* create_deck(){
  Deck* d;
  int i;
  for(i=0;i<52;i++){
    d->cards[i] = create_card();
    if(!(d->cards[i])) return NULL;
  }
  return d;
}


void delete_deck(Deck *d){
  int i;
  for(i=0;i<52;i++){
    d->cards[i] = delete_card();
  }
  free(d);
}


Deck *set_deck(Deck *d){
  char suits[4][10] = ["Spades","Clubs","Hearts","Diamonds"];
  char card_names[13][10] = ["Ace","Two","Three","Four","Five","Six","Seven","Eight","Nine","Ten","Jack","King","Queen"];

  int i,j,k;
  k = 0;

  for(i=0;i<4;i++){
    for(j=0;j<13;j++){
      if(j=>10){
        d->cards[k] = set_card(d->cards[k],card_names[j],suits[i],10);
        k++;
        break;
      }
      d->cards[k] = set_card(d->cards[k],card_names[j],suits[i],(j+1));
      k++;
    }
  }

  return d;

}
