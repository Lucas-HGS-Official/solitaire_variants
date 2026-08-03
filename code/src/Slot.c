#include "Slot.h"

#include <raylib.h>

#include "Card.h"


Slot *init_slot(Vector2 slot_pos, Card *card_template) {
    Slot *new_slot = MemAlloc(sizeof(Slot));

    for (int i=0; i<200; i++) {
        new_slot->pile[i] = (Card) {0};
    }
    new_slot->bottom = (Card) {0};
    new_slot->top = (Card) {0};
    new_slot->size = 0;

    new_slot->rect = card_template->spr.dest_rec;
    new_slot->rect.x = slot_pos.x;
    new_slot->rect.y = slot_pos.y;

    return new_slot;
}
void update_slot(Slot *slot) {

    return;
}
void draw_slot(Slot *slot) {
    Rectangle slot_bg = slot->rect;

    DrawRectangleRec(slot_bg, RAYWHITE);
    DrawRectangleLinesEx(slot_bg, 5.f, DARKBLUE);

    if (slot->size) {
        draw_card(&slot->top);
    }

    return;
}
void destroy_slot(Slot *slot) {
    MemFree(slot);

    return;
}
