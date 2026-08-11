#pragma once

#include <stdbool.h>

#include <raylib.h>
#include <raymath.h>

#include "CardSet.h"
#include "Slot.h"


Card *init_card(Vector2 test_card_pile);
Card instance_card(CardSet *card_set, CARD_SUIT suit, CARD_NUM num, Pile *test_card_pile);
void draw_card(Card *card);
void update_card(Card *card, float dt);
void destroy_card(Card *card);
