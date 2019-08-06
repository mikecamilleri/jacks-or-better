/*
    Jacks or Better
    Copyright (C) 2019 Michael Camilleri <mike@mikecamilleri.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

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
