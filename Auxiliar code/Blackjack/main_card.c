#include "card.h"
#include <stdio.h>

void main(){
  Card *c[4];


int i;

for(i=0;i<4;i++){
  c[i]= create_card();
  if(!c[i]){
    printf("ERROR2");
    return;
  }
}



c[0]= set_card(c[0],"Pato","Lucia",69);

if(!c[0]){
  printf("ERROR3");
  return;
}

c[1]= set_card(c[1],"Arbol","Juan",67);

if(!c[1]){
  printf("ERROR4");
  return;
}

c[2]= set_card(c[2],"iou","vhjgsas",90);

if(!c[2]){
  printf("ERROR5");
  return;
}

c[3]= set_card(c[3],"sdlfdilf","ddfjgsd",567);

if(!c[3]){
  printf("ERROR6");
  return;
}

 printf("vas bien loco\n");



for(i=0;i<4;i++){
  print_card(c[i], stdout);
}



for(i=0;i<4;i++){
  delete_card(c[i]);
}


}
