#pragma once

#include <Sprite.h>


typedef enum CARD_SUIT {
    HEARTS_SUIT,
    DIAMONDS_SUIT,

    CLUBS_SUIT,
    SPADES_SUIT,

    NUM_SUIT,
} CARD_SUIT;

typedef enum CARD_NUM {
    ACE_NUM,
    TWO_NUM,
    THREE_NUM,
    FOUR_NUM,
    FIVE_NUM,
    SIX_NUM,
    SEVEN_NUM,
    EIGHT_NUM,
    NINE_NUM,
    TEN_NUM,
    JACK_NUM,
    QUEEN_NUM,
    KING_NUM,

    SPECIALS_NUM,

    NUM_CARD_NUM,
} CARD_NUM;


typedef struct Card {
    Sprite *spr;
    CARD_NUM num;
    CARD_SUIT suit;
} Card;


Card *init_cards(void);
void draw_card(Card *card);
void update_card(Card *card);
void destroy_cards(Card *card);
