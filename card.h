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
