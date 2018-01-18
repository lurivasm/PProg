#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main(void){
  char *a, *b, *aux;

  aux = (char*)malloc(sizeof(char)*2000);
  fgets(aux, 500, stdin);
  printf("%s", aux);
  fgets(aux, 500, stdin);
  printf("%s", aux);
  return;
}
