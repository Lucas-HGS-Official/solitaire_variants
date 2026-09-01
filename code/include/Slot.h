#pragma once

#include <stdbool.h>

#include <raylib.h>
#include <raymath.h>

#include "CardSet.h"


// slots hold 1 card
typedef struct Slot {
    Card card;
    Card card_back;
    Rectangle rect;
    bool is_faceup;
} Slot;


Slot *init_slot(Vector2 slot_pos, CardSet *card_set);
void update_slot(Slot *slot);
void draw_slot(Slot *slot);
void destroy_slot(Slot *slot);

void put_card_in_slot(Slot *slot, Card *card);
Card take_card_from_slot(Slot *slot);
