#pragma once

#include <raylib.h>
#include <raymath.h>

#include "CardSet.h"


void init_scene(CardSet *resources_card_set);
void update_scene(float dt);
void draw_scene(void);
void destroy_scene(void);
