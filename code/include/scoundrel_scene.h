#pragma once

#include <raylib.h>
#include <raymath.h>

#include "CardSet.h"


void init_scoundrel(CardSet *resources_card_set);
void update_scoundrel(float dt);
void draw_scoundrel(void);
void destroy_scoundrel(void);
