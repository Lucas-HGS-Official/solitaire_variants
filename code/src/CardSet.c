#include "CardSet.h"

#include <raylib.h>

#include "Card.h"


CardSet *init_cardset(Card *card) {
    CardSet *new_set = MemAlloc(sizeof(CardSet));

    CARD_SUIT suit = HEARTS_SUIT;
    CARD_NUM num = ACE_NUM;
    for (int i=0; i<DECK_SIZE; i++) {
        new_set->cards[i] = *card;

        change_card_face(&new_set->cards[i], num, suit);

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

    change_card_face(&new_set->blank, SPECIALS_NUM, HEARTS_SUIT);
    change_card_face(&new_set->back, SPECIALS_NUM, DIAMONDS_SUIT);
    change_card_face(&new_set->joker_red, SPECIALS_NUM, CLUBS_SUIT);
    change_card_face(&new_set->joker_black, SPECIALS_NUM, SPADES_SUIT);

    return new_set;
}
void update_cardset(CardSet *card_set) {

    return;
}
void destroy_cardset(CardSet *card_set) {
    MemFree(card_set);

    return;
}
