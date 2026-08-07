#pragma once

#include <stdbool.h>

#include "settings.h"

#include "CardSet.h"


typedef struct Slot {
    Card pile[200];
    Card top;
    Card bottom;
    Rectangle rect;
    int size;
    bool is_faceup;
} Slot;


Slot *init_slot(Vector2 slot_pos, Card *card_template);
void update_slot(Slot *slot);
void draw_slot(Slot *slot);
void destroy_slot(Slot *slot);

void add_card_to_slot(Slot *slot, Card *card);
