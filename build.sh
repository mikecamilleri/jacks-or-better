#!/usr/bin/env bash

cc -std=c99 -lncurses card.c deck.c hand.c gamestate.c ui.c main.c -o jacks-or-better
