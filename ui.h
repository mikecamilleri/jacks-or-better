#ifndef UI_H
#define UI_H

#include "card.h"
#include "gamestate.h"

#define CH_BET_INCREMENT '='
#define CH_BET_DECREMENT '-'
#define CH_HOLD_0 '1'
#define CH_HOLD_1 '2'
#define CH_HOLD_2 '3'
#define CH_HOLD_3 '4'
#define CH_HOLD_4 '5'
#define CH_DEAL '\n'
#define CH_DRAW '\n'
#define CH_NEW_GAME 'n'
#define CH_EXIT 'x'

#define UI_SLEEP_MICROSECONDS 250000

void uiInit(GameState *main_gs_ptr);
void uiBetUpdate();
void uiHandDeal();
void uiHandDraw();
void uiHandClear();
void uiResultUpdate();
void uiHeldsUpdate();
void uiPaidUpdate();
void uiCreditUpdate();
void uiCardUpdate();
void uiBackgroundUpdate();
void uiExit(int n);
void uiSigWinchHandler(int sig);

#endif /* UI_H */
