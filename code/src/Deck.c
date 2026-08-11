#include "Deck.h"

#include <raylib.h>
#include <stdbool.h>

#include "CardSet.h"
#include "Pile.h"


Pile *init_deck(CardSet *card_set, Vector2 deck_pos) {
    Pile *new_deck;
    new_deck = init_pile(deck_pos, card_set);
    new_deck->is_faceup = false;

    for (int i=0; i<DECK_SIZE-1; i++) {
        Card card_to_push = card_set->cards[i];
        push_card_to_pile(new_deck, &card_to_push);
    }

    return new_deck;
}
void update_deck(Pile *deck) {

    return;
}
void draw_deck(Pile *deck) {
    draw_pile(deck);

    return;
}
void destroy_deck(Pile *deck) {
    destroy_pile(deck);

    return;
}
