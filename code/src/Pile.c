#include "Pile.h"

#include "CardLose.h"
#include "CardSet.h"


Pile *init_pile(Vector2 pile_pos, CardSet *card_set) {
    Pile *new_pile = MemAlloc(sizeof(Pile));

    for (int i=0; i<MAX_CARDS; i++) {
        new_pile->pile[i] = (Card) {0};
    }
    new_pile->bottom = (Card) {0};
    new_pile->top = (Card) {0};
    new_pile->size = 0;
    new_pile->is_faceup = true;

    new_pile->rect = card_set->blank.spr.dest_rec;
    new_pile->rect.x = pile_pos.x;
    new_pile->rect.y = pile_pos.y;

    return new_pile;
}
void update_pile(Pile *pile) {

    return;
}
void draw_pile(Pile *pile) {
    Rectangle pile_bg = pile->rect;

    DrawRectangleRec(pile_bg, RAYWHITE);
    DrawRectangleLinesEx(pile_bg, 5.f, DARKBLUE);

    if (pile->size) {
        draw_card(&pile->top);
    }

    return;
}
void destroy_pile(Pile *pile) {
    MemFree(pile);

    return;
}
void push_card_to_pile(Pile *pile, Card *card) {
    if (!card->is_active) {
        return;
    }
    for (int i=0; i<MAX_CARDS; i++) {
        if (!pile->pile[i].is_active) {
            pile->pile[i] = *card;
            pile->top = *card;
            if (!pile->is_faceup) {
                change_card_face(&pile->top, SPECIALS_NUM, DIAMONDS_SUIT);
            }
            pile->top.spr.dest_rec.x = pile->rect.x;
            pile->top.spr.dest_rec.y = pile->rect.y;
            pile->size++;

            card->is_active = false;

            break;
        }
    }

    return;
}
Card pop_card_from_pile(Pile *pile, CardSet *card_set) {
    Card card_from_pile = {0};

    Card *top_card = {0};
    Card *new_top_card = {0};
    for (int i=0; i<MAX_CARDS; i++) {
        if (!pile->pile[i].is_active) {
            break;
        }
        top_card = &pile->pile[i];
        new_top_card = &pile->pile[i-1];
    }
    card_from_pile = *top_card;
    *top_card = (Card) {0};
    pile->size--;

    pile->top = *new_top_card;
    if (!pile->is_faceup) {
        change_card_face(&pile->top, SPECIALS_NUM, DIAMONDS_SUIT);
    }

    return card_from_pile;
}


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
Card take_card_from_slot(Slot *slot, CardSet *card_set) {
    Card card_from_slot = {0};
    card_from_slot = slot->card;
    slot->card = (Card) {0};

    return card_from_slot;
}
