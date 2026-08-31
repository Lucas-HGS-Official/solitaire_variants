#include "game.h"

#include <stdlib.h>

#include "settings.h"

#include "CardSet.h"
#include "scoundrel_scene.h"
#include "scene.h"


static SCENE_STATE current_scene = 0;

static CardSet *card_set = NULL;


static void _update_game(float dt);
static void _draw_game(void);


void game_init(void) {
    // Initializing Raylib and the window and it's functions
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, GAME_NAME);
    InitAudioDevice();
    SetTargetFPS(60);

    // Initializing a CardSet struct with all possible cards
    card_set = init_cardset();

    // TODO: move this to loop
    // TODO: create initial menu scene where other scenes can be selected
    current_scene = SCOUNDREL_SCENE;
    switch (current_scene) {
        case TEST_SCENE:
            init_scene(card_set);
            break;
        case SCOUNDREL_SCENE:
            init_scoundrel(card_set);
            break;
        case SCENE_NUM:
            break;
    }

    return;
}

// Main game loop
void game_loop(void) {
    while (!WindowShouldClose()) {
        _update_game(GetFrameTime());
        _draw_game();
    }

    return;
}

void game_close(void) {
    // Releases the memory that the opened scene reserved
    switch (current_scene) {
        case TEST_SCENE:
            destroy_scene();
            break;
        case SCOUNDREL_SCENE:
            destroy_scoundrel();
            break;
        case SCENE_NUM:
            break;
    }
    destroy_cardset(card_set);

    CloseAudioDevice();
    CloseWindow();

    return;
}


void _update_game(float dt) {
    // Calls the update function for the currently opened scene before drawing
    switch (current_scene) {
        case TEST_SCENE:
            update_scene(dt);
            break;
        case SCOUNDREL_SCENE:
            update_scoundrel(dt);
            break;
        case SCENE_NUM:
            break;
    }

    return;
}
void _draw_game(void) {
    // Using the BeginDrawing and EndDrawing function from Raylib
    BeginDrawing();

    // Calls the draw function for the currently opened scene
    switch (current_scene) {
        case TEST_SCENE:
            draw_scene();
            break;
        case SCOUNDREL_SCENE:
            draw_scoundrel();
            break;
        case SCENE_NUM:
            break;
    }

    EndDrawing();

    return;
}
