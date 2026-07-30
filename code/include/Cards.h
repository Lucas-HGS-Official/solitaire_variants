#pragma once

#include <Sprite.h>


typedef struct Card {
    Sprite *spr;
    int col;
    int row;
} Card;


Card *init_cards(void);
void draw_card(Card *card);
void destroy_cards(Card *card);
