#include "scene.h"

#include <stdlib.h>

#include "CardSet.h"
#include "CardLose.h"
#include "Slot.h"


Card *card_template = NULL;
CardSet *card_set = NULL;
Slot *card_slot = NULL;


void init_scene(void) {
    card_set = init_cardset();

    card_template = MemAlloc(sizeof(Card));
    *card_template = instance_card(card_set, CLUBS_SUIT, ACE_NUM, (Vector2) { 10, 10 });

    card_slot = init_slot((Vector2) { 10, 10 }, card_template);

    return;
}
void update_scene(float dt) {
    update_card(card_template, dt);

    Vector2 card_pos = { card_template->spr.dest_rec.x, card_template->spr.dest_rec.y };
    if (Vector2Distance(card_pos, card_template->last_slot) <= 1.f && !card_template->is_pickup) {
        add_card_to_slot(card_slot, card_template);
    }

    return;
}
void draw_scene(void) {
    ClearBackground(SKYBLUE);

    draw_slot(card_slot);
    draw_card(card_template);

    return;
}
void destroy_scene(void) {
    destroy_slot(card_slot);
    destroy_cardset(card_set);
    destroy_card(card_template);

    return;
}
