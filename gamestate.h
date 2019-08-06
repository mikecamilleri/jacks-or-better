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

#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <stdbool.h>
#include "deck.h"
#include "hand.h"

#define RESULT_LEN 16
#define PAY_TABLE_LEN 9
#define BET_MAX 5
#define BET_MIN 1
#define CREDIT_MAX 1000000 // 1,000,000

typedef struct GameState {
    long int credit;
    int bet;
    int paid;
    char result[RESULT_LEN];
    Deck deck;
    Hand hand;
} GameState;

void gsInit(GameState *main_gs_ptr);
void gsClear();
void gsDeckPopulate();
void gsShuffle();
void gsDeal();
void gsDraw();
void gsHandClear();
void gsHeldToggle(int x);
bool gsIsHeld(int x);
void gsResultSet(const char *s);
void gsResultClear();
void gsBetIncrement();
void gsBetDecrement();
void gsDebitBet();
bool gsBetIsTooHigh();
void gsCreditPaid();
bool gsPaidIsTooHigh();
void gsSetResultAndPaid();

typedef struct PayLine {
    const char *name;
    int bet1, bet2, bet3, bet4, bet5;
    bool (*isMatch) (Hand *);
} PayLine;

const PayLine PAY_TABLE [PAY_TABLE_LEN];

#endif /* GAMESTATE_H */
