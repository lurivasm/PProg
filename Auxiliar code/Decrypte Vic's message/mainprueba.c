/*Main de prueba*/

#include "message.h"

void main(void){
  int a;

a = message_game("/home/lurivasm/Documents/PPROG/Decrypte Vic's message/messages.txt");

  if( a == ERR) printf("\n\nerror");
  if( a == WIN) printf("\n\nganaste");
  if( a == LOOSE) printf("\n\nperdiste pero funciona:)");
  return;
}
