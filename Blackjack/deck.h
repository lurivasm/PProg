#ifndef DECK_H
#define DECK_H

#include "card.h"

typedef struct _deck Deck;

Deck* create_deck();

void delete_deck(Deck *d);

Deck* set_deck(Deck *d);

Card* deck_get_card(Deck *d,int key);

Deck* shuffle(Deck *d);

#endif
