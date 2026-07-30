#include "Cards.h"
#include "Sprite.h"
#include <raylib.h>


Card *init_cards(void) {
    Card *card = MemAlloc(sizeof(Card));
    Sprite *cards_spr = MemAlloc(sizeof(Sprite));
    init_sprite(cards_spr, "resources/cardsLarge_tilemap_packed.png");
    card->spr = cards_spr;

    cards_spr->src_rec.width /= 14;
    cards_spr->src_rec.height /= 4;

    cards_spr->dest_rec.width /= 14;
    cards_spr->dest_rec.height /= 4;

    return card;
}
void draw_card(Card *cards) {
    draw_sprite(cards->spr, cards->spr->tint);

    return;
}
void destroy_cards(Card *card) {
    destroy_sprite(card->spr);
    MemFree(card);

    return;
}
