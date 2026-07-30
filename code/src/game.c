#include "game.h"

#include <raylib.h>
#include <stdlib.h>

#include "Settings.h"

#include "Sprite.h"
#include "Cards.h"


Card *cards_spr = NULL;


void _update_game(float dt);
void _draw_game(void);


void game_init(void) {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, GAME_NAME);
    InitAudioDevice();
    SetTargetFPS(60);

    cards_spr = init_cards();

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
    destroy_cards(cards_spr);

    CloseAudioDevice();
    CloseWindow();

    return;
}


void _update_game(float dt) {

    return;
}
void _draw_game(void) {
    BeginDrawing();
        ClearBackground(DARKGRAY);

        draw_card(cards_spr);

    EndDrawing();
    return;
}
