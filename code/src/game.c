#include "game.h"

#include <raylib.h>

#include "Settings.h"


void _update_game(float dt);
void _draw_game(void);


void game_init(void) {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, GAME_NAME);
    InitAudioDevice();
    SetTargetFPS(60);

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
    CloseAudioDevice();
    CloseWindow();

    return;
}


void _update_game(float dt) {

    return;
}
void _draw_game(void) {
    BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

    EndDrawing();
    return;
}
