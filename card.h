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

#ifndef CARD_H
#define CARD_H

enum suit_nos {
    SUIT_C, SUIT_D, SUIT_H, SUIT_S,
    SUITS_LEN = 4, SUIT_NULL = -1
};

enum rank_nos {
    RANK_2, RANK_3, RANK_4, RANK_5, RANK_6, RANK_7, RANK_8, RANK_9,
    RANK_T, RANK_J, RANK_Q, RANK_K, RANK_A,
    RANKS_LEN = 13, RANK_NULL = -1
};

typedef struct Card {
    int rank_no;
    int suit_no;
} Card;

#endif /* CARD_H */
