#include "CardSet.h"

#include "Card.h"
#include "Sprite.h"


CardSet *init_cardset(void) {
    Card card_template = {0};
    init_sprite(&card_template.spr, "resources/cardsLarge_tilemap_packed.png");
    card_template.num = ACE_NUM;
    card_template.suit = CLUBS_SUIT;

    card_template.speed = 400.f;
    card_template.is_pickup = false;
    card_template.is_active = true;

    card_template.spr.src_rec.width /= NUM_CARD_NUM;
    card_template.spr.src_rec.height /= NUM_SUIT;

    card_template.spr.dest_rec.width /= NUM_CARD_NUM;
    card_template.spr.dest_rec.height /= NUM_SUIT;

    CardSet *new_set = MemAlloc(sizeof(CardSet));

    CARD_SUIT suit = HEARTS_SUIT;
    CARD_NUM num = ACE_NUM;
    for (int i=0; i<DECK_SIZE; i++) {
        new_set->cards[i] = card_template;

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
