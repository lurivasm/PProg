#ifndef DECK_H
#define DECK_H

#include "card.h"

typedef struct _deck Deck;

Deck* create_deck();

void delete_deck(Deck *d);

Deck* set_deck(Deck *d);

Card* deck_get_card(Deck *d,int key);

Deck* shuffle(Deck *d);

int deck_find_card_value(Deck *d,int value,int from);

void deck_card_swap(Deck* d, int c1,int c2);

#endif
