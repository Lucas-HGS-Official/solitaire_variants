#pragma once

#include "CardSet.h"
#include "Slot.h"


// typedef Slot Deck;


Slot *init_deck(CardSet *card_set, Vector2 deck_pos);
void update_deck(Slot *deck);
void draw_deck(Slot *deck);
void destroy_deck(Slot *deck);
