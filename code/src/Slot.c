#include "Slot.h"

#include <raylib.h>
#include <stdbool.h>

#include "CardSet.h"
#include "LooseCard.h"


Slot *init_slot(Vector2 slot_pos, CardSet *card_set) {
    Slot *new_slot = MemAlloc(sizeof(Slot));

    new_slot->card = (Card) {0};
    new_slot->is_faceup = true;

    new_slot->rect = card_set->blank.spr.dest_rec;
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

    if (slot->card.is_active) {
        if (slot->is_faceup) {
            draw_card(&slot->card);
        } else {
            draw_card(&slot->card_back);
        }
    }

    return;
}
void destroy_slot(Slot *slot) {
    MemFree(slot);

    return;
}
void put_card_in_slot(Slot *slot, Card *card) {
    if (!card->is_active) {
        return;
    }
    if (!slot->card.is_active) {
        slot->card = *card;
        slot->card.spr.dest_rec.x = slot->rect.x;
        slot->card.spr.dest_rec.y = slot->rect.y;

        card->is_active = false;
    }

    return;
}
Card take_card_from_slot(Slot *slot) {
    Card card_from_slot = {0};
    card_from_slot = slot->card;
    slot->card = (Card) {0};

    return card_from_slot;
}
