#include "Card.h"

#include <raylib.h>
#include <raymath.h>
#include <stdbool.h>

#include "Sprite.h"


void _card_pickup(Card *card);


Card *init_card(void) {
    Card *card = MemAlloc(sizeof(Card));
    Sprite *cards_spr = MemAlloc(sizeof(Sprite));
    init_sprite(cards_spr, "resources/cardsLarge_tilemap_packed.png");
    card->spr = cards_spr;
    card->num = ACE_NUM;
    card->suit = CLUBS_SUIT;

    card->is_pickup = false;

    cards_spr->src_rec.width /= NUM_CARD_NUM;
    cards_spr->src_rec.height /= NUM_SUIT;
    change_card_face(card, card->num, card->suit);

    cards_spr->dest_rec.width /= NUM_CARD_NUM;
    cards_spr->dest_rec.height /= NUM_SUIT;

    return card;
}
void draw_card(Card *cards) {
    draw_sprite(cards->spr, cards->spr->tint);

    return;
}
void change_card_face(Card *card, CARD_NUM new_card_num, CARD_SUIT new_card_suit) {
    card->num = new_card_num;
    card->suit = new_card_suit;
    card->spr->src_rec.x = card->spr->src_rec.width * card->num;
    card->spr->src_rec.y = card->spr->src_rec.height * card->suit;

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
    change_card_face(card, card->num, card->suit);
    _card_pickup(card);

    return;
}
void destroy_card(Card *card) {
    destroy_sprite(card->spr);
    MemFree(card);

    return;
}


void _card_pickup(Card *card) {
    Vector2 mouse_card_delta = {0};
    Vector2 mouse_pos = GetMousePosition();
    Vector2 card_pos = { .x=card->spr->dest_rec.x, .y=card->spr->dest_rec.y };
    if (CheckCollisionPointRec(mouse_pos, card->spr->dest_rec) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        card->mouse_xydelta = Vector2Subtract(mouse_pos, card_pos);
        card->is_pickup = true;
    }
    if (card->is_pickup && IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
        card->is_pickup = false;
    } else if (card->is_pickup) {
        card->spr->dest_rec.x = mouse_pos.x - card->mouse_xydelta.x;
        card->spr->dest_rec.y = mouse_pos.y - card->mouse_xydelta.y;
    }

    return;
}
