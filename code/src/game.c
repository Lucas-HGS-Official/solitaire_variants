#include "game.h"

#include <raylib.h>
#include <stdlib.h>

#include "Settings.h"

#include "Deck.h"
#include "Card.h"


Card *card = NULL;
Deck *deck = NULL;


void _update_game(float dt);
void _draw_game(void);


void game_init(void) {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, GAME_NAME);
    InitAudioDevice();
    SetTargetFPS(60);

    card = init_card();
    deck = init_deck(card);

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
    destroy_deck(deck);
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
        ClearBackground(DARKGRAY);

        draw_card(card);

    EndDrawing();
    return;
}
