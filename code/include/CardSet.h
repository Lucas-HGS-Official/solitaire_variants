#pragma once

#include <raylib.h>

#include "Card.h"


#define DECK_SIZE 52


typedef struct CardSet {
    Card cards[52];
    Card blank;
    Card back;
    Card joker_red;
    Card joker_black;
} CardSet;


CardSet *init_deck(Card *card);
void update_deck(CardSet *card_set);
void destroy_deck(CardSet *card_set);
