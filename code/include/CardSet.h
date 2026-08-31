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

    // SPECIALS_NUM are the non-standard faces from the texture, such as jokers, blanks and backs
    SPECIALS_NUM,

    NUM_CARD_NUM,
} CARD_NUM;


typedef struct Card {
    Sprite spr;

    CARD_NUM num;
    CARD_SUIT suit;

    Vector2 mouse_xydelta; // to hold the position of mouse relative to the card while the card is picked up
    Vector2 placement; // position where the card returns when not picked up

    // for card movement
    Vector2 direction;
    float speed;

    bool is_pickup; // determines if the card is currently held by the player
    bool is_active; // determines when the card being used
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
