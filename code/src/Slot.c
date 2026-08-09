#include "Slot.h"

#include "CardLose.h"
#include "CardSet.h"


Slot *init_slot(Vector2 slot_pos, CardSet *card_set) {
    Slot *new_slot = MemAlloc(sizeof(Slot));

    for (int i=0; i<MAX_CARDS; i++) {
        new_slot->pile[i] = (Card) {0};
    }
    new_slot->bottom = (Card) {0};
    new_slot->top = (Card) {0};
    new_slot->size = 0;
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

    if (slot->size) {
        draw_card(&slot->top);
    }

    return;
}
void destroy_slot(Slot *slot) {
    MemFree(slot);

    return;
}
void push_card_to_slot(Slot *slot, Card *card) {
    if (!card->is_active) {
        return;
    }
    for (int i=0; i<MAX_CARDS; i++) {
        if (!slot->pile[i].is_active) {
            slot->pile[i] = *card;
            slot->top = *card;
            if (!slot->is_faceup) {
                change_card_face(&slot->top, SPECIALS_NUM, DIAMONDS_SUIT);
            }
            slot->top.spr.dest_rec.x = slot->rect.x;
            slot->top.spr.dest_rec.y = slot->rect.y;
            slot->size++;

            card->is_active = false;

            break;
        }
    }

    return;
}
Card pop_card_from_slot(Slot *slot, CardSet *card_set) {
    Card card_from_slot = {0};

    Card *top_card = {0};
    Card *new_top_card = {0};
    for (int i=0; i<MAX_CARDS; i++) {
        if (!slot->pile[i].is_active) {
            break;
        }
        top_card = &slot->pile[i];
        new_top_card = &slot->pile[i-1];
    }
    card_from_slot = *top_card;
    *top_card = (Card) {0};

    slot->top = *new_top_card;
    if (!slot->is_faceup) {
        change_card_face(&slot->top, SPECIALS_NUM, DIAMONDS_SUIT);
    }

    return card_from_slot;
}
