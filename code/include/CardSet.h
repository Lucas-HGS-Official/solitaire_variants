#pragma once

#include "settings.h"

#include "Card.h"


#define DECK_SIZE 52


typedef struct CardSet {
    Card cards[52];
    Card blank;
    Card back;
    Card joker_red;
    Card joker_black;
} CardSet;


CardSet *init_cardset(Card *card);
void update_cardset(CardSet *card_set);
void destroy_cardset(CardSet *card_set);
