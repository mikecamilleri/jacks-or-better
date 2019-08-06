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
