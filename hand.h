#ifndef HAND_H
#define HAND_H

#include <stdbool.h>
#include "card.h"

#define HAND_LEN 5

typedef struct Hand {
    bool helds[HAND_LEN];
    Card cards[HAND_LEN];
} Hand;

void handClear(Hand *h);
bool handIsRoyalFlush(Hand *h);
bool handIsStraightFlush(Hand *h);
bool handIsFourOfAKind(Hand *h);
bool handIsFullHouse(Hand *h);
bool handIsFlush(Hand *h);
bool handIsStraight(Hand *h);
bool handIsThreeOfAKind(Hand *h);
bool handIsTwoPair(Hand *h);
bool handIsJacksOrBetter(Hand *h);

#endif /* HAND_H */
