#include "Deck.h"

#include <raylib.h>
#include <stdbool.h>

#include "CardSet.h"
#include "Slot.h"


Deck *init_deck(CardSet *card_set, Vector2 deck_pos) {
    Deck *new_deck;
    new_deck = init_slot(deck_pos, card_set);
    new_deck->is_faceup = false;

    for (int i=0; i<DECK_SIZE; i++) {
        push_card_to_slot(new_deck, &card_set->cards[i]);
    }

    return new_deck;
}
void update_deck(Deck *deck) {

    return;
}
void draw_deck(Deck *deck) {
    draw_slot(deck);

    return;
}
void destroy_deck(Deck *deck) {
    destroy_slot(deck);

    return;
}
