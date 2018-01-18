#include "number.h"

void main(void){
  int a;
  a = number_game();

  if(a == WIN) printf("\nGANASTEEEEEEE");
  else if(a == ERR) printf("\nPETASTEEEEEEE");
  else printf("\nPETASTE PERO PERDIENDO JODETE QUE NO GANARÁS NUNCA A JUAN\nMUAJAJAJAJAJAJAJA");

  return;
}
