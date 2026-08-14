#pragma once

#include <raylib.h>
#include <raymath.h>


typedef enum SCENE_STATE {
    TEST_SCENE,
    SCOUNDREL_SCENE,

    SCENE_NUM,
} SCENE_STATE;


void game_init(void);
void game_loop(void);
void game_close(void);
