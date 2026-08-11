#include "Deck.h"

#include <raylib.h>
#include <stdbool.h>

#include "CardSet.h"
#include "Slot.h"


Slot *init_deck(CardSet *card_set, Vector2 deck_pos) {
    Slot *new_deck;
    new_deck = init_slot(deck_pos, card_set);
    new_deck->is_faceup = false;

    for (int i=0; i<DECK_SIZE-1; i++) {
        Card card_to_push = card_set->cards[i];
        push_card_to_slot(new_deck, &card_to_push);
    }

    return new_deck;
}
void update_deck(Slot *deck) {

    return;
}
void draw_deck(Slot *deck) {
    draw_slot(deck);

    return;
}
void destroy_deck(Slot *deck) {
    destroy_slot(deck);

    return;
}
