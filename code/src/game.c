#include "game.h"

#include <raylib.h>
#include <stdlib.h>

#include "Settings.h"

#include "CardSet.h"
#include "Card.h"
#include "Slot.h"


Card *card = NULL;
CardSet *card_set = NULL;
Slot *card_slot = NULL;


void _update_game(float dt);
void _draw_game(void);


void game_init(void) {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, GAME_NAME);
    InitAudioDevice();
    SetTargetFPS(60);

    card = init_card();
    card_set = init_cardset(card);
    card_slot = init_slot((Vector2) { 0, 0 }, card);

    return;
}

void game_loop(void) {
    while (!WindowShouldClose()) {
        _update_game(GetFrameTime());
        _draw_game();
    }

    return;
}

void game_close(void) {
    destroy_slot(card_slot);
    destroy_cardset(card_set);
    destroy_card(card);

    CloseAudioDevice();
    CloseWindow();

    return;
}


void _update_game(float dt) {
    update_card(card);

    return;
}
void _draw_game(void) {
    BeginDrawing();
        ClearBackground(SKYBLUE);

        draw_slot(card_slot);
        draw_card(card);

    EndDrawing();
    return;
}
