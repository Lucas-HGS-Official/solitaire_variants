#pragma once

#include <stdbool.h>

#include <raylib.h>
#include <raymath.h>

#include "CardSet.h"


typedef struct Pile {
    Card pile[MAX_CARDS];
    Card top;
    Card bottom;
    Rectangle rect;
    int size;
    bool is_faceup;
} Pile;


Pile *init_pile(Vector2 pile_pos, CardSet *card_set);
void update_pile(Pile *pile);
void draw_pile(Pile *pile);
void destroy_pile(Pile *pile);

void push_card_to_pile(Pile *pile, Card *card);
Card pop_card_from_pile(Pile *pile, CardSet *card_set);
