#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main(void){
  int n, i;
  char *a, *b;


  FILE *f;
  f = fopen("/home/lurivasm/Documents/PPROG/PProg/PProg/Decrypte Vic's message/messages.txt","r");
  if(!f) return;

  while(!feof(f)){
    fscanf(f, "%d", &n);
    for(i = 0; i <= n; i++) fscanf(f, "%c", a+i);
    for(i = 0; i <= n; i++) fscanf(f, "%c", b+i);
    fprintf(stdout, "%d %s %s", n, a, b);
  }
  fclose(f);
}
