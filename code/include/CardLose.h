#pragma once

#include <stdbool.h>

#include <raylib.h>
#include <raymath.h>

#include "CardSet.h"


Card *init_card(Vector2 test_card_pile);
Card instance_card(CardSet *card_set, CARD_SUIT suit, CARD_NUM num, Vector2 card_placement);
void draw_card(Card *card);
void update_card(Card *card, float dt);
void destroy_card(Card *card);

void pickup_card(Card *card);
void move_card_to_placement(Card *card, float dt);
