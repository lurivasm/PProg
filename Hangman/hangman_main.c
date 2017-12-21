#include <stdio.h>
#include <stdlib.h>
#include "hangman.h"

int main() {
	hangman* hm;
	hm= hangman_ini("hangman_test.txt");
	if(hm==NULL) {
		return 0;
	}
	hangman_play (hm, stdout, stdin);
	hangman_destroy(hm);
	return 1;

}
