#include "scene.h"

#include <stdlib.h>

#include "CardSet.h"
#include "Card.h"
#include "Slot.h"


Card *card = NULL;
CardSet *card_set = NULL;
Slot *card_slot = NULL;


void init_scene(void) {
    card = init_card((Vector2) { 0, 0 });
    card_set = init_cardset(card);
    card_slot = init_slot((Vector2) { 0, 0 }, card);

    return;
}
void update_scene(float dt) {
    update_card(card, dt);

    return;
}
void draw_scene(void) {
    ClearBackground(SKYBLUE);

    draw_slot(card_slot);
    draw_card(card);

    return;
}
void destroy_scene(void) {
    destroy_slot(card_slot);
    destroy_cardset(card_set);
    destroy_card(card);

    return;
}
