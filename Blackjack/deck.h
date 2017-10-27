#ifndef CARD_H
#define CARD_H

#include "card.h"

typedef struct _deck Deck;

Deck* create_deck();

void delete_deck(Deck *d);

Deck *set_deck(Deck *d);

Card *deck_get_firstcard(Deck *d);

Card* shuffle(Deck *d);

#endif
