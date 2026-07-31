#include "Cards.h"

#include <raylib.h>
#include <raymath.h>
#include <stdio.h>

#include "Sprite.h"

void _change_card_face(Card *card);
void _card_pickup(Card *card);


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
    _card_pickup(card);

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
void _card_pickup(Card *card) {
    Vector2 mouse_card_delta = {0};
    Vector2 mouse_pos = GetMousePosition();
    Vector2 card_pos = { .x=card->spr->dest_rec.x, .y=card->spr->dest_rec.y };
    if (CheckCollisionPointRec(mouse_pos, card->spr->dest_rec)) {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            mouse_card_delta = (Vector2) { .x=mouse_pos.x - card_pos.x, .y=mouse_pos.y - card_pos.y };
        }
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            // mouse_pos = GetMousePosition();
            printf("\n card: (x=%.2f, y=%.2f)\n", card_pos.x, card_pos.y);
            printf(" mouse: (x=%.2f, y=%.2f)\n", mouse_pos.x, mouse_pos.y);
            printf(" delta: (x=%.2f, y=%.2f)\n", mouse_card_delta.x, mouse_card_delta.y);
            card->spr->dest_rec.x = mouse_pos.x - mouse_card_delta.x;
            card->spr->dest_rec.y = mouse_pos.y - mouse_card_delta.y;
        }
    }

    return;
}
