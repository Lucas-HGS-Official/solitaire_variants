#include "Deck.h"

#include <raylib.h>

#include "Card.h"


Deck *init_deck(Card *card) {
    Deck *new_deck = MemAlloc(sizeof(Deck));

    CARD_SUIT suit = HEARTS_SUIT;
    CARD_NUM num = ACE_NUM;
    for (int i=0; i<DECK_SIZE; i++) {
        new_deck->cards[i] = *card;

        change_card_face(&new_deck->cards[i], num, suit);

        num++;
        if (num > KING_NUM) {
            num = ACE_NUM;
            suit++;
        }
        if (suit > SPADES_SUIT) {
            suit = HEARTS_SUIT;
            num = ACE_NUM;
        }
    }

    change_card_face(&new_deck->blank, SPECIALS_NUM, HEARTS_SUIT);
    change_card_face(&new_deck->back, SPECIALS_NUM, DIAMONDS_SUIT);
    change_card_face(&new_deck->joker_red, SPECIALS_NUM, CLUBS_SUIT);
    change_card_face(&new_deck->joker_black, SPECIALS_NUM, SPADES_SUIT);

    return new_deck;
}
void update_deck(Deck *deck) {

    return;
}
void destroy_deck(Deck *deck) {
    MemFree(deck);

    return;
}
