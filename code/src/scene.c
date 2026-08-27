#include "scene.h"

#include <raylib.h>
#include <stdbool.h>
#include <stdlib.h>

#include "CardSet.h"
#include "CardLose.h"
#include "Deck.h"
#include "Pile.h"


Card card_list[MAX_CARDS] = {0};
CardSet *card_set = NULL;
Pile *card_pile = NULL;
Pile *deck = NULL;
Slot *test_slot = NULL;


void init_scene(CardSet *resources_card_set) {
    card_set = resources_card_set;

    deck = init_deck(card_set, (Vector2) { 200, 150 });
    card_pile = init_pile((Vector2) { 900, 200 }, card_set);
    test_slot = init_slot((Vector2) { 10, 10 }, card_set);

    Vector2 pile_pos = (Vector2) { card_pile->rect.x, card_pile->rect.y };
    card_list[0] = instance_card(card_set, CLUBS_SUIT, ACE_NUM, pile_pos);
    card_list[0].placement = (Vector2) { 10, 10 };


    return;
}
void update_scene(float dt) {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        if (CheckCollisionPointRec(GetMousePosition(), card_pile->rect)) {
            for (int i=0; i<MAX_CARDS; i++) {
                if (!card_list[i].is_active) {
                    card_list[i] = pop_card_from_pile(card_pile);
                    card_list[i].is_pickup = true;
                    break;
                }
            }
        }
    }
    update_slot(test_slot);

    if (IsKeyPressed(KEY_S)) {
        Vector2 mouse_pos = GetMousePosition();
        int rand_suit = GetRandomValue(HEARTS_SUIT, SPADES_SUIT);
        int rand_num = GetRandomValue(ACE_NUM, KING_NUM);
        for (int i=0; i<MAX_CARDS; i++) {
            if (!card_list[i].is_active) {
                Vector2 pile_pos = (Vector2) { card_pile->rect.x, card_pile->rect.y };
                card_list[i] = instance_card(card_set, rand_suit, rand_num, pile_pos);
                break;
            }
        }
    }

    for (int i=0; i<MAX_CARDS; i++) {
        if (!card_list[i].is_active) {
            continue;
        }
        Vector2 card_pos = { card_list[i].spr.dest_rec.x, card_list[i].spr.dest_rec.y };
        if (Vector2Distance(card_pos, card_list[i].placement) <= 1.f && !card_list[i].is_pickup) {
            push_card_to_pile(card_pile, &card_list[i]);
        }
        // update_card(&card_list[i], dt);

        pickup_card(&card_list[i]);
        move_card_to_placement(&card_list[i], dt);
    }

    return;
}
void draw_scene(void) {
    ClearBackground(SKYBLUE);
    DrawFPS(10, 10);

    draw_deck(deck);
    draw_pile(card_pile);
    draw_slot(test_slot);
    for (int i=0; i<MAX_CARDS; i++) {
        if (card_list[i].is_active) {
            draw_card(&card_list[i]);
        }
    }

    return;
}
void destroy_scene(void) {
    destroy_pile(card_pile);
    destroy_deck(deck);
    destroy_slot(test_slot);

    return;
}
