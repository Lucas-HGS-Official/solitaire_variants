#pragma once

#include <raylib.h>
#include <raymath.h>


// Defining scenes for each solitaire variant game for the player to chose
typedef enum SCENE_STATE {
    TEST_SCENE,
    SCOUNDREL_SCENE,

    SCENE_NUM,
} SCENE_STATE;


void game_init(void);
void game_loop(void);
void game_close(void);
