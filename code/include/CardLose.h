#pragma once

#include <stdbool.h>

#include "settings.h"

#include "CardSet.h"


Card *init_card(Vector2 test_card_slot);
Card instance_card(CardSet *card_set, CARD_SUIT suit, CARD_NUM num, Vector2 test_card_slot);
void draw_card(Card *card);
void update_card(Card *card, float dt);
void destroy_card(Card *card);
