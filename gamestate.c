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

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "card.h"
#include "deck.h"
#include "gamestate.h"
#include "hand.h"

const char *TRY_AGAIN_STR = "TRY AGAIN";

const PayLine PAY_TABLE[PAY_TABLE_LEN] = {
    {"ROYAL FLUSH",    250, 500, 750, 1000, 4000, handIsRoyalFlush},
    {"STRAIGHT FLUSH",  50, 100, 150,  200,  250, handIsStraightFlush},
    {"4 OF A KIND",     25,  50,  75,  100,  125, handIsFourOfAKind},
    {"FULL HOUSE",       9,  18,  27,   36,   45, handIsFullHouse},
    {"FLUSH",            6,  12,  18,   24,   30, handIsFlush},
    {"STRAIGHT",         4,   8,  12,   16,   20, handIsStraight},
    {"3 OF A KIND",      3,   6,   9,   12,   15, handIsThreeOfAKind},
    {"TWO PAIR",         2,   4,   6,    8,   10, handIsTwoPair},
    {"JACKS OR BETTER",  1,   2,   3,    4,    5, handIsJacksOrBetter}
};

GameState *gs_ptr;

void gsInit(GameState *main_gs_ptr) {
    srand((unsigned long)time(NULL));
    gs_ptr = main_gs_ptr;
    gs_ptr->credit = 1000;
    gs_ptr->bet = 1;
    gsDeckPopulate();
    gsClear();
}

void gsClear() {
    gs_ptr->paid = 0;
    gsResultClear();
    gsHandClear();
    gsShuffle();
}

void gsDeckPopulate() {
    deckPopulate(&gs_ptr->deck);
}

void gsShuffle() {
    deckShuffle(&gs_ptr->deck);
}

void gsDeal() {
    int i = 0;
    for (i = 0; i < HAND_LEN; i++) {
        gs_ptr->hand.cards[i] = deckDraw(&gs_ptr->deck);
    }
}

void gsDraw() {
    int i = 0;
    for (i = 0; i < HAND_LEN; i++) {
        if (gs_ptr->hand.helds[i] == true) continue;
        gs_ptr->hand.cards[i] = deckDraw(&gs_ptr->deck);
    }
}

void gsHandClear() {
    handClear(&gs_ptr->hand);
}

void gsHeldToggle(int card_no) {
    if (card_no < 0 || card_no >= HAND_LEN) return;
    gs_ptr->hand.helds[card_no] = (gs_ptr->hand.helds[card_no] ? false : true);
}

bool gsIsHeld(int card_no) {
    if (card_no < 0 || card_no >= HAND_LEN) return false;
    return gs_ptr->hand.helds[card_no];
}

void gsResultSet(const char *s) {
    strncpy(gs_ptr->result, s, RESULT_LEN);
}

void gsResultClear() {
    gsResultSet("");
}

void gsBetIncrement() {
    if (gs_ptr->bet < BET_MAX) gs_ptr->bet++;
}

void gsBetDecrement() {
    if (gs_ptr->bet > BET_MIN) gs_ptr->bet--;
}

void gsDebitBet() {
    if (!gsBetIsTooHigh()) gs_ptr->credit -= gs_ptr->bet;
}

bool gsBetIsTooHigh() {
    return (gs_ptr->credit - gs_ptr->bet < 0);
}

void gsCreditPaid() {
    !gsPaidIsTooHigh() ? (gs_ptr->credit += gs_ptr->paid) : (gs_ptr->credit = CREDIT_MAX);
}

bool gsPaidIsTooHigh() {
    return (gs_ptr->credit + gs_ptr->paid > CREDIT_MAX);
}

void gsSetResultAndPaid() {
    int i = 0;
    for (i = 0; i < PAY_TABLE_LEN; i++) {
        if (PAY_TABLE[i].isMatch(&gs_ptr->hand)) {
            // set paid
            switch (gs_ptr->bet) {
                case 1: gs_ptr->paid = PAY_TABLE[i].bet1; break;
                case 2: gs_ptr->paid = PAY_TABLE[i].bet2; break;
                case 3: gs_ptr->paid = PAY_TABLE[i].bet3; break;
                case 4: gs_ptr->paid = PAY_TABLE[i].bet4; break;
                case 5: gs_ptr->paid = PAY_TABLE[i].bet5; break;
            }
            // set result text
            gsResultSet(PAY_TABLE[i].name);
            return;
        }
    }
    gsResultSet(TRY_AGAIN_STR);
}
