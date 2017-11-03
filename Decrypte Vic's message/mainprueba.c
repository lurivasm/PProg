/*Main de prueba*/

#include "message.h"

void main(void){
  int a;

a = message_game("/home/alumnos/e359558/Desktop/Decrypte Vic's message/messages.txt");

  if( a == ERR) printf("\n\nerror");
  if( a == WIN) printf("\n\nganaste");
  if( a == LOOSE) printf("\n\nperdiste pero funciona:)");
  return;
}
