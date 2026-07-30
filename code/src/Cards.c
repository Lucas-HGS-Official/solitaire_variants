#include "Cards.h"

#include <raylib.h>

#include "Sprite.h"

void _change_card_face(Card *card);


Card *init_cards(void) {
    Card *card = MemAlloc(sizeof(Card));
    Sprite *cards_spr = MemAlloc(sizeof(Sprite));
    init_sprite(cards_spr, "resources/cardsLarge_tilemap_packed.png");
    card->spr = cards_spr;
    card->num = ACE_NUM;
    card->suit = CLUBS_SUIT;

    cards_spr->src_rec.width /= NUM_CARD_NUM;
    cards_spr->src_rec.height /= NUM_SUIT;
    _change_card_face(card);

    cards_spr->dest_rec.width /= NUM_CARD_NUM;
    cards_spr->dest_rec.height /= NUM_SUIT;

    return card;
}
void draw_card(Card *cards) {
    draw_sprite(cards->spr, cards->spr->tint);

    return;
}
void update_card(Card *card) {
    if (IsKeyPressed(KEY_S)) {
        card->suit++;
        if (card->suit >= NUM_SUIT) {
            card->suit = HEARTS_SUIT;
        }
    }
    if (IsKeyPressed(KEY_N)) {
        card->num++;
        if (card->num >= NUM_CARD_NUM) {
            card->num = ACE_NUM;
        }
    }
    _change_card_face(card);

    return;
}
void destroy_cards(Card *card) {
    destroy_sprite(card->spr);
    MemFree(card);

    return;
}


void _change_card_face(Card *card) {
    card->spr->src_rec.x = card->spr->src_rec.width * card->num;
    card->spr->src_rec.y = card->spr->src_rec.height * card->suit;

    return;
}
