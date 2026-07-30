#pragma once

#include <Sprite.h>


typedef enum CARD_SUIT {
    HEARTS_SUIT,
    DIAMONDS_SUIT,

    CLUBS_SUIT,
    SPADES_SUIT,

    NUM_SUIT,
} CARD_SUIT;


typedef struct Card {
    Sprite *spr;
    int col;
    CARD_SUIT suit;
} Card;


Card *init_cards(void);
void draw_card(Card *card);
void update_card(Card *card);
void destroy_cards(Card *card);
