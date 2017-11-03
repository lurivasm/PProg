#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main(void){
  char *a, *b, *aux;
  int n;

//  a = (char*)malloc(sizeof(char)*20);
//  b = (char*)malloc(sizeof(char)*20);
  aux = (char*)malloc(sizeof(char)*2000);
  FILE *f;
  f = fopen("messages.txt","r");


  while(!feof(f)){
    fgets(aux, 50, f);
    if (strlen(aux)>3) {
        fprintf(stdout, "%s\n", aux);
     a = strtok(aux, "/");
        b = strtok(NULL, "/");
      fprintf(stdout, "%s  %s\n", a, b);
    }
}

  fclose(f);
//  free(a);
//  free(b);
  free(aux);
}
