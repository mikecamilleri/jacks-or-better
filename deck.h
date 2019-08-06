#ifndef DECK_H
#define DECK_H

#include "card.h"

#define DECK_LEN 52

typedef struct Deck {
    int draw_idx;
    Card cards[DECK_LEN];
} Deck;

void deckPopulate(Deck *d);
void deckShuffle(Deck *d);
Card deckDraw(Deck *d);

#endif /* DECK_H */
