#ifndef CARD_H
#define CARD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR -2

typedef struct _card Card;

Card* create_card();

void delete_card(Card* c);

Card* set_card(Card* c,char* name,char* suit,int value);

char* card_get_name(Card* c);

char* card_get_suit(Card* c);

int card_get_value(Card* c);

void print_card(Card *c,FILE *f);

Card* card_copy(Card *c1,Card *c2);

#endif
