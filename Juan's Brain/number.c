
#include "number.h"

int number_compare(int number, int answer){
  if (number <= 0 || answer <= 0) return ERR;
  return (number == answer) ? 0 : 1;
}


int number_rand(int min, int max){
  return min+(rand()%(max-min+1));
}


int number_game(void){
  int i, number[5], answer, errs = 0, comp;
  srand(time(NULL));

  for(i = 0; i < 6; i++){
    number[i] = number_rand(0, 1000);
    if(number[i] == -1) return ERR;

    printf("\n%d\nYour answer:", number[i]);
    scanf("%d", &answer);
    comp = number_compare(number[i], answer);

    if(comp == ERR) return ERR;
    if(comp == 1) errs ++;
    if(errs > 2) return LOOSE;
  }

  return WIN;
}
