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

#include <locale.h>
#include <math.h>
#include <ncurses.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "card.h"
#include "hand.h"
#include "ui.h"

// TODO: the pay table should be generated from the code
const char *UI_BACKGROUND_STR =
"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"
"$  ROYAL FLUSH ...... | 250 | 500 | 750 | 1000 | *4000 |                       $"
"$  STRAIGHT FLUSH ... |  50 | 100 | 150 |  200 |   250 |                       $"
"$  4 OF A KIND ...... |  25 |  50 |  75 |  100 |   125 |   J a c k s           $"
"$  FULL HOUSE ....... |   9 |  18 |  27 |   36 |    45 |       - o r -         $"
"$  FLUSH ............ |   6 |  12 |  18 |   24 |    30 |         B e t t e r   $"
"$  STRAIGHT ......... |   4 |   8 |  12 |   16 |    20 |                       $"
"$  3 OF A KIND ...... |   3 |   6 |   9 |   12 |    15 |                       $"
"$  TWO PAIR ......... |   2 |   4 |   6 |    8 |    10 |   / \\   o   ^ ^  / \\  $"
"$  JACKS OR BETTER .. |   1 |   2 |   3 |    4 |     5 |   \\ /  o|o   v   -|-  $"
"$                                                                              $"
"$                                                                              $"
"$  +-------+  +-------+  +-------+  +-------+  +-------+                       $"
"$  |       |  |       |  |       |  |       |  |       |   DEAL/DRAW  [ENTER]  $"
"$  |       |  |       |  |       |  |       |  |       |   HOLD         [1-5]  $"
"$  |       |  |       |  |       |  |       |  |       |   BET          [+/-]  $"
"$  |       |  |       |  |       |  |       |  |       |   EXIT           [X]  $"
"$  +-------+  +-------+  +-------+  +-------+  +-------+                       $"
"$        [1]        [2]        [3]        [4]        [5]                       $"
"$                                                                              $"
"$  PAID                    BET            CREDIT                               $"
"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$(MC)$$$";

const char *HELD_STR = "HELD";

const char *UI_CARD_RANKS[RANKS_LEN] = {
    "2", "3", "4", "5", "6", "7", "8", "9", 
    "10", "J", "Q",  "K", "A"
};

const char *UI_CARD_SUITS[SUITS_LEN] = {
    "\u2663\n     o \n    o|o",   // club
    "\u2666\n    / \\\n    \\ /", // diamond
    "\u2665\n    ^ ^\n     v ",   // heart
    "\u2660\n    / \\\n    -|-"   // spade
};

GameState *gs_ptr;
WINDOW *ui_background;
WINDOW *ui_cards[HAND_LEN];
WINDOW *ui_helds[HAND_LEN];
WINDOW *ui_result;
WINDOW *ui_paid;
WINDOW *ui_bet;
WINDOW *ui_credit;

void uiInit(GameState *main_gs_ptr) {
    gs_ptr = main_gs_ptr;

    // set up signals
    signal(SIGWINCH, uiSigWinchHandler);

    // set up ncurses
    setlocale(LC_ALL,"en_US.utf-8");
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    keypad(stdscr, true);
    refresh();

    // set up windows (height, width, row, col)
    ui_background = newwin(22, 80, 0, 0);

    ui_cards[0] = newwin(6, 9, 12, 3);
    ui_cards[1] = newwin(6, 9, 12, 14);
    ui_cards[2] = newwin(6, 9, 12, 25);
    ui_cards[3] = newwin(6, 9, 12, 36);
    ui_cards[4] = newwin(6, 9, 12, 47);

    ui_helds[0] = newwin(1, 4, 18, 4);
    ui_helds[1] = newwin(1, 4, 18, 15);
    ui_helds[2] = newwin(1, 4, 18, 26);
    ui_helds[3] = newwin(1, 4, 18, 37);
    ui_helds[4] = newwin(1, 4, 18, 48);

    ui_result = newwin(1, 16, 11, 21);
    ui_paid = newwin(1, 4, 20, 8);
    ui_bet = newwin(1, 1, 20, 31);
    ui_credit = newwin(1, 7, 20, 49);

    refresh();

    uiBackgroundUpdate();
    uiPaidUpdate();
    uiBetUpdate();
    uiCreditUpdate();
}

void uiBetUpdate() {
    mvwprintw(ui_bet, 0, 0, "%d", gs_ptr->bet);
    wrefresh(ui_bet);
}

void uiHandDeal() {
    int i = 0;
    uiHandClear();
    usleep(UI_SLEEP_MICROSECONDS);
    // print the new cards
    for(int i = 0; i < HAND_LEN; i++) {
        uiCardUpdate(i);
        usleep(UI_SLEEP_MICROSECONDS);
    }
}

void uiHandDraw() {
    int i = 0;
    // clear the cards
    for (i = 0; i < HAND_LEN; i++) {
        if (gsIsHeld(i)) continue;
        wclear(ui_cards[i]);
        wrefresh(ui_cards[i]);
    }
    usleep(UI_SLEEP_MICROSECONDS);
    // print the new cards
    for(int i = 0; i < HAND_LEN; i++) {
        if (gsIsHeld(i)) continue;
        uiCardUpdate(i);
        usleep(UI_SLEEP_MICROSECONDS);
    }
}

void uiHandClear() {
    int i = 0;
    // clear the cards
    for (i = 0; i < HAND_LEN; i++) {
        wclear(ui_cards[i]);
        wrefresh(ui_cards[i]);
    }
}

void uiHeldsUpdate() {
    int i = 0;
    // clear all helds
    for (i = 0; i < HAND_LEN; i++) {
        wclear(ui_helds[i]);
        wrefresh(ui_helds[i]);
    }
    // update
    for(int i = 0; i < HAND_LEN; i++) {
        if (gsIsHeld(i)) mvwprintw(ui_helds[i], 0, 0, HELD_STR);
        wrefresh(ui_helds[i]);
    }
}

void uiResultUpdate() {
    wclear(ui_result);
    wmove(ui_result, 0, (17 - strlen(gs_ptr->result)) / 2);
    wprintw(ui_result, gs_ptr->result);
    wrefresh(ui_result);
}

void uiPaidUpdate() {
    wclear(ui_paid);
    mvwprintw(ui_paid, 0, 0, "%d", gs_ptr->paid);
    wrefresh(ui_paid);
}

void uiCreditUpdate() {
    long int n = 0;
    wclear(ui_credit);
    // calulate number of digits in gs_ptr->credit and move cursor
    wmove(ui_credit, 0, 6 - (int)log10(gs_ptr->credit));
    wprintw(ui_credit, "%d", gs_ptr->credit);
    wrefresh(ui_credit);
}

void uiCardUpdate(int x) {
    if (x < 0 || x >= HAND_LEN) return;
    wclear(ui_cards[x]);
    if (gs_ptr->hand.cards[x].rank_no < 0 || gs_ptr->hand.cards[x].suit_no < 0) return;
    mvwprintw(ui_cards[x], 1, 2, UI_CARD_RANKS[gs_ptr->hand.cards[x].rank_no]);
    mvwprintw(ui_cards[x], 2, 2, UI_CARD_SUITS[gs_ptr->hand.cards[x].suit_no]);
    wborder(ui_cards[x], '|', '|', '-', '-', '+', '+', '+', '+');
    wrefresh(ui_cards[x]);
}

void uiBackgroundUpdate() {
    mvwprintw(ui_background, 0, 0, UI_BACKGROUND_STR);
    wrefresh(ui_background);
}

void uiExit(int n) {
    endwin(); // teardown ncurses
    exit(n);  // exit the program
}

// TODO: this needs some work
void uiSigWinchHandler(int sig) {
    refresh();
}
