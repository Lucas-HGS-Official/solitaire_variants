#pragma once

#include "CardSet.h"
#include "Pile.h"


Pile *init_deck(CardSet *card_set, Vector2 deck_pos);
void update_deck(Pile *deck);
void draw_deck(Pile *deck);
void destroy_deck(Pile *deck);
