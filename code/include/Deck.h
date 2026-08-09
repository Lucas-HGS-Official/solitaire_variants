#pragma once

#include "CardSet.h"
#include "Slot.h"


typedef Slot Deck;


Deck *init_deck(CardSet *card_set, Vector2 deck_pos);
void update_deck(Deck *deck);
void draw_deck(Deck *deck);
void destroy_deck(Deck *deck);
