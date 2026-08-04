#pragma once

#include <raylib.h>
#include <stdbool.h>

#include "Sprite.h"


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
    Sprite spr;
    CARD_NUM num;
    CARD_SUIT suit;
    Vector2 mouse_xydelta;
    Vector2 last_slot;
    Vector2 direction;
    float speed;
    bool is_pickup;
    bool is_active;
} Card;


Card *init_card(Vector2 test_card_slot);
void draw_card(Card *card);
void change_card_face(Card *card, CARD_NUM new_card_num, CARD_SUIT new_card_suit);
void update_card(Card *card, float dt);
void destroy_card(Card *card);
