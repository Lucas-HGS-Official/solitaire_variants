#include "CardLose.h"

#include <raylib.h>
#include <stdbool.h>

#include "CardSet.h"
#include "Pile.h"
#include "Sprite.h"


void _card_pickup(Card *card);
void _move_card_to_pile(Card *card, float dt);


Card instance_card(CardSet *card_set, CARD_SUIT suit, CARD_NUM num, Pile *test_card_pile) {
    Card new_card = card_set->cards[(suit+1) * num];
    new_card.placement = (Vector2) { test_card_pile->rect.x, test_card_pile->rect.y };

    return new_card;
}
void draw_card(Card *card) {
    if (card->is_active) {
        draw_sprite(&card->spr, card->spr.tint);
    }

    return;
}
void update_card(Card *card, float dt) {
    if (card->is_active) {
        _card_pickup(card);
        _move_card_to_pile(card, dt);
    }

    return;
}
void destroy_card(Card *card) {
    MemFree(card);

    return;
}


void _card_pickup(Card *card) {
    Vector2 mouse_pos = GetMousePosition();
    Vector2 card_pos = { .x=card->spr.dest_rec.x, .y=card->spr.dest_rec.y };
    if (CheckCollisionPointRec(mouse_pos, card->spr.dest_rec) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        card->mouse_xydelta = Vector2Subtract(mouse_pos, card_pos);
        card->is_pickup = true;
    }
    if (card->is_pickup && IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
        card->is_pickup = false;
    } else if (card->is_pickup) {
        card->spr.dest_rec.x = mouse_pos.x - card->mouse_xydelta.x;
        card->spr.dest_rec.y = mouse_pos.y - card->mouse_xydelta.y;
    }

    return;
}
void _move_card_to_pile(Card *card, float dt) {
    if (card->placement.x == 0 && card->placement.y == 0) {
        return;
    }
    Vector2 card_pos = { card->spr.dest_rec.x, card->spr.dest_rec.y };
    if (Vector2Distance(card_pos, card->placement) < 10.f) {
        card->spr.dest_rec.x = card->placement.x;
        card->spr.dest_rec.y = card->placement.y;

        return;
    } else if (!card->is_pickup) {
        card->direction = Vector2Normalize(Vector2Subtract(card->placement, card_pos));

        card->spr.dest_rec.x += card->direction.x * card->speed * dt;
        card->spr.dest_rec.y += card->direction.y * card->speed * dt;
    }

    return;
}
