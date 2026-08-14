#include "game.h"

#include "settings.h"

#include "scene.h"


static SCENE_STATE current_scene = 0;


void _update_game(float dt);
void _draw_game(void);


void game_init(void) {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, GAME_NAME);
    InitAudioDevice();
    SetTargetFPS(60);
    current_scene = TEST_SCENE;

    switch (current_scene) {
        case TEST_SCENE:
            init_scene();
            break;

        case SCENE_NUM:
            break;
    }


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
    switch (current_scene) {
        case TEST_SCENE:
            destroy_scene();
            break;
        case SCENE_NUM:
            break;
    }

    CloseAudioDevice();
    CloseWindow();

    return;
}


void _update_game(float dt) {
    switch (current_scene) {
        case TEST_SCENE:
            update_scene(dt);
            break;
        case SCENE_NUM:
            break;
    }

    return;
}
void _draw_game(void) {
    BeginDrawing();
    switch (current_scene) {
        case TEST_SCENE:
            draw_scene();
            break;
        case SCENE_NUM:
            break;
    }

    EndDrawing();
    return;
}
