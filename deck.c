#include <stdlib.h> 
#include "card.h"
#include "deck.h"

void deckPopulate(Deck *d) {
    int i = 0, r = 0, s = 0;
    d->draw_idx = 0;
    for (i = 0; i < DECK_LEN; i++) {
        d->cards[i].rank_no = r;
        d->cards[i].suit_no = s;
        if (r == RANKS_LEN - 1) {
            r = 0; // restart with first rank
            s++;   // start new suite
        } else {
            r++;   // next rank
        }
    }
}

void deckShuffle(Deck *d) {
    int i = 0, r = 0;
    Card c;
    d->draw_idx = 0;
    // iterate through deck, swap each card with random index
    for (i = 0; i < DECK_LEN; i++) {
        r = rand() % DECK_LEN;
        c = d->cards[i];
        d->cards[i] = d->cards[r];
        d->cards[r] = c;
    }
}

Card deckDraw(Deck *d) {
    Card c = {.rank_no = RANK_NULL, .suit_no = SUIT_NULL};
    if (d->draw_idx < DECK_LEN) {
        c = d->cards[d->draw_idx];
        d->draw_idx++;
    }
    return c;
}
