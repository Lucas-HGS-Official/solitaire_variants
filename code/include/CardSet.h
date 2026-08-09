#pragma once

#include <raylib.h>
#include <raymath.h>

#include "Sprite.h"


#define MAX_CARDS 200

#define DECK_SIZE 52

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

typedef struct CardSet {
    Card cards[DECK_SIZE];
    Card blank;
    Card back;
    Card joker_red;
    Card joker_black;
} CardSet;


CardSet *init_cardset(void);
void update_cardset(CardSet *card_set);
void change_card_face(Card *card, CARD_NUM new_card_num, CARD_SUIT new_card_suit);
void destroy_cardset(CardSet *card_set);
