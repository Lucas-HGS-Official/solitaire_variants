#pragma once

#include <raylib.h>

#include "Card.h"


#define DECK_SIZE 52


typedef struct Deck {
    Card cards[52];
} Deck;


Deck *init_deck(Card *card);
void update_deck(Deck *deck);
void destroy_deck(Deck *deck);
