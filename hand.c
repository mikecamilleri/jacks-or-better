#include <stdbool.h>
#include "card.h"
#include "hand.h"

void handClear(Hand *h) {
    int i = 0;
    for (i = 0; i < HAND_LEN; i++) {
        h->cards[i].rank_no = RANK_NULL;
        h->cards[i].suit_no = SUIT_NULL;
        h->helds[i] = false;
    }
}

// a flush containing 10, J, Q, K, A
bool handIsRoyalFlush(Hand *h) {
    int i = 0;
    if (!handIsFlush(h)) return false;
    for (i = 0; i < HAND_LEN; i++) {
        switch (h->cards[i].rank_no) {
            case RANK_T: break;
            case RANK_J: break;
            case RANK_Q: break;
            case RANK_K: break;
            case RANK_A: break;
            default: return false;
        }
    }
    return true;
}

// both a straight and a flush
bool handIsStraightFlush(Hand *h) {
    return (handIsStraight(h) && handIsFlush(h));
}

// four cards of the same rank
bool handIsFourOfAKind(Hand *h) {
    int i = 0, j = 0, n = 0;
    for (i = 0; i < RANKS_LEN; i++) {
        n = 0;
        for (j = 0; j < HAND_LEN; j++) {
            if (h->cards[j].rank_no == i) n++;
        };
        if (n >= 4) return true;
    }
    return false;
}

// one set of two of the same rank, and one set of three of the same rank
bool handIsFullHouse(Hand *h) {
    return (handIsTwoPair(h) && handIsThreeOfAKind(h));
}

// five of the same suite
bool handIsFlush(Hand *h) {
    int i = 0, sc = 0, sd = 0, sh = 0, ss = 0;
    for (i = 0; i < HAND_LEN; i++) {
        switch (h->cards[i].suit_no) {
            case SUIT_C: sc++; break;
            case SUIT_D: sd++; break;
            case SUIT_H: sh++; break;
            case SUIT_S: ss++; break;
        }
    }
    return (sc == HAND_LEN || sd == HAND_LEN || sh == HAND_LEN || ss == HAND_LEN);
}

// five cards of sequential rank
bool handIsStraight(Hand *h) {
    int i = 0, j = 0, lr = 0, r = 0;
    // find the lowest ranking card
    lr = 100; // arbitrary high number
    for (i = 0; i < HAND_LEN; i++) {
        // we need to handle an Ace in special way becasue it can be high or low
        // in this case we treat it as low since it can't be the low ranking 
        // card if it is high.
        (h->cards[i].rank_no == RANK_A) ? (r = -1) : (r = h->cards[i].rank_no);
        if (r < lr) lr = r;
    }
    r = lr; // set r to the current rank
    // count cards incrementing rank 
    // need four in addition to the low ranking card so start with i = 1
    // in other words, we already took care of the first card above
    for (i = 1; i < HAND_LEN; i++) {
        // check each card to see if it is one greater than the current low
        // raking card
        for (j = 0; j < HAND_LEN; j++) {
            if (h->cards[j].rank_no == (r + 1)) {
                r = h->cards[j].rank_no; // set r to the current rank
                break;
            }
        }
        // we can stop here if there was no card one greater than the current
        // low ranking card
        if (lr + i != r) return false;
    }
    return true;
}

// three cards of the same rank
bool handIsThreeOfAKind(Hand *h) {
    int i = 0, j = 0, n = 0;
    for (i = 0; i < RANKS_LEN; i++) {
        n = 0;
        for (j = 0; j < HAND_LEN; j++) {
            if (h->cards[j].rank_no == i) n++;
        }
        if (n >= 3) return true;
    }
    return false;
}

// two sets of two cards of the same rank
bool handIsTwoPair(Hand *h) {
    int i = 0, j = 0, nr = 0, np = 0;
    // nr: number of current rank
    // np: number of pairs
    for (i = 0; i < RANKS_LEN; i++) {
        nr = 0;
        for (j = 0; j < HAND_LEN; j++) {
            if (h->cards[j].rank_no == i) nr++;
        }
        if (nr >= 2) np++;
    }
    return (np >= 2);
}

// JJ, QQ, KK, or AA
bool handIsJacksOrBetter(Hand *h) {
    int i = 0, rj = 0, rq = 0, rk = 0, ra = 0;
    for (i = 0; i < HAND_LEN; i++) {
        switch (h->cards[i].rank_no) {
            case RANK_J: rj++; break;
            case RANK_Q: rq++; break;
            case RANK_K: rk++; break;
            case RANK_A: ra++; break;
        }
    }
    return (rj >= 2 || rq >= 2 || rk >= 2 || ra >= 2);
}
