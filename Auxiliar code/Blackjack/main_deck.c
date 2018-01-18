#include "deck.h"

int main(){
  Deck *d;
  int i;
  d = create_deck();
  if(!d) {
    printf("ERROR1");
    return 0;
  }


d = set_deck(d);
if(!d) {
  printf("ERROR2");
  return 0;
}



d= shuffle(d);
if(!d) {
  printf("ERROR3");
  return 0;
}
 for(i=0;i<52;i++){
   print_card(deck_get_card(d,i),stdout);
 }

 delete_deck(d);
 return 1;
}
