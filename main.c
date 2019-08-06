#include <locale.h>
#include <ncurses.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "gamestate.h"
#include "ui.h"

GameState gs;

int main(void) {
    int i = 0, ch = 0;

    gsInit(&gs); // initailize game state
    uiInit(&gs); // initailize UI

    // game loop
    while (true) {
        gsClear();

        // adjust bet, request deal
        do {
            ch = getch();
            switch (ch) {
                case CH_BET_INCREMENT:
                    gsBetIncrement();
                    // We update the hand, helds, and paid paid here to  
                    // replicate casino machine behavior. These should be 
                    // displayed until bet adjustment or deal.  
                    uiHandClear();
                    uiHeldsUpdate();
                    uiResultUpdate();
                    uiPaidUpdate();
                    uiBetUpdate();
                    break;
                case CH_BET_DECREMENT:
                    gsBetDecrement();
                    uiHandClear();
                    uiHeldsUpdate();
                    uiResultUpdate();
                    uiPaidUpdate();
                    uiBetUpdate();
                    break;
                case CH_EXIT:
                    uiExit(1);
                    break;
                default:
                    break;
            }
            
        } while (ch != CH_DEAL);

        // debit bet, deal (includes shuffle)
        gsDebitBet();
        gsDeal();
        uiHeldsUpdate();
        uiResultUpdate();
        uiPaidUpdate();
        uiCreditUpdate();
        uiHandDeal();

        // hold, request draw
        do {
            ch = getch();
            switch (ch) {
                case CH_HOLD_0:
                    gsHeldToggle(0);
                    uiHeldsUpdate();
                    break;
                case CH_HOLD_1:
                    gsHeldToggle(1);
                    uiHeldsUpdate();
                    break;
                case CH_HOLD_2:
                    gsHeldToggle(2);
                    uiHeldsUpdate();
                    break;
                case CH_HOLD_3:
                    gsHeldToggle(3);
                    uiHeldsUpdate();
                    break;
                case CH_HOLD_4:
                    gsHeldToggle(4);
                    uiHeldsUpdate();
                    break;
                case CH_EXIT:
                    uiExit(1);
                    break;
            }
        } while (ch != CH_DRAW);

        // draw, determine result, credit win
        gsDraw();
        gsSetResultAndPaid();
        gsCreditPaid();
        uiHandDraw();
        uiResultUpdate();
        uiPaidUpdate();
        uiCreditUpdate();
    }

    // flow should never reach here
    uiExit(1);  // a bad thing just happened
    return 1;  // a very bad thing just happened
}
