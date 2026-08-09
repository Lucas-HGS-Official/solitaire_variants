#include "scene.h"

#include <raylib.h>
#include <stdbool.h>
#include <stdlib.h>

#include "CardSet.h"
#include "CardLose.h"
#include "Deck.h"
#include "Slot.h"


Card card_list[MAX_CARDS] = {0};
// Card *card_template = NULL;
CardSet *card_set = NULL;
Slot *card_slot = NULL;
Deck *deck = NULL;


void init_scene(void) {
    card_set = init_cardset();

    // deck = init_deck(card_set, (Vector2) { 10, 10 });
    card_slot = init_slot((Vector2) { 900, 200 }, card_set);

    card_list[0] = instance_card(card_set, CLUBS_SUIT, ACE_NUM, card_slot);


    return;
}
void update_scene(float dt) {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        if (CheckCollisionPointRec(GetMousePosition(), card_slot->rect)) {
            card_list[0] = pop_card_from_slot(card_slot, card_set);
            card_list[0].is_pickup = true;
        }
    }

    Vector2 card_pos = { card_list[0].spr.dest_rec.x, card_list[0].spr.dest_rec.y };
    if (Vector2Distance(card_pos, card_list[0].last_slot) <= 1.f && !card_list[0].is_pickup) {
        push_card_to_slot(card_slot, &card_list[0]);
    }

    update_card(&card_list[0], dt);

    return;
}
void draw_scene(void) {
    ClearBackground(SKYBLUE);

    // draw_deck(deck);
    draw_slot(card_slot);
    draw_card(&card_list[0]);

    return;
}
void destroy_scene(void) {
    destroy_slot(card_slot);
    // destroy_deck(deck);

    destroy_cardset(card_set);

    return;
}
