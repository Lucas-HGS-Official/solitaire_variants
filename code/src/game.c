#include "game.h"

#include "scene.h"


void _update_game(float dt);
void _draw_game(void);


void game_init(void) {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, GAME_NAME);
    InitAudioDevice();
    SetTargetFPS(60);
    init_scene();


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
    destroy_scene();

    CloseAudioDevice();
    CloseWindow();

    return;
}


void _update_game(float dt) {
    update_scene(dt);

    return;
}
void _draw_game(void) {
    BeginDrawing();
    draw_scene();

    EndDrawing();
    return;
}
