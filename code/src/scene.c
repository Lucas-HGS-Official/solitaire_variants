#include "scene.h"

#include <raylib.h>
#include <stdbool.h>
#include <stdlib.h>

#include "CardSet.h"
#include "CardLose.h"
#include "Deck.h"
#include "Slot.h"


Card card_list[MAX_CARDS] = {0};
CardSet *card_set = NULL;
Pile *card_pile = NULL;
Pile *deck = NULL;


void init_scene(void) {
    card_set = init_cardset();

    deck = init_deck(card_set, (Vector2) { 25, 30 });
    card_pile = init_pile((Vector2) { 900, 200 }, card_set);

    card_list[0] = instance_card(card_set, CLUBS_SUIT, ACE_NUM, card_pile);


    return;
}
void update_scene(float dt) {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        if (CheckCollisionPointRec(GetMousePosition(), card_pile->rect)) {
            for (int i=0; i<MAX_CARDS; i++) {
                if (!card_list[i].is_active) {
                    card_list[i] = pop_card_from_pile(card_pile, card_set);
                    card_list[i].is_pickup = true;
                    break;
                }
            }
        }
    }

    if (IsKeyPressed(KEY_S)) {
        Vector2 mouse_pos = GetMousePosition();
        int rand_suit = GetRandomValue(HEARTS_SUIT, SPADES_SUIT);
        int rand_num = GetRandomValue(ACE_NUM, KING_NUM);
        for (int i=0; i<MAX_CARDS; i++) {
            if (!card_list[i].is_active) {
                card_list[i] = instance_card(card_set, rand_suit, rand_num, card_pile);
                break;
            }
        }
    }

    for (int i=0; i<MAX_CARDS; i++) {
        if (card_list[i].is_active) {
            Vector2 card_pos = { card_list[i].spr.dest_rec.x, card_list[i].spr.dest_rec.y };
            if (Vector2Distance(card_pos, card_list[i].last_pile) <= 1.f && !card_list[i].is_pickup) {
                push_card_to_pile(card_pile, &card_list[i]);
            }
            update_card(&card_list[i], dt);
        }
    }

    return;
}
void draw_scene(void) {
    ClearBackground(SKYBLUE);
    DrawFPS(10, 10);

    draw_deck(deck);
    draw_pile(card_pile);
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

    destroy_cardset(card_set);

    return;
}
