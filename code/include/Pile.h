#pragma once

#include <stdbool.h>

#include <raylib.h>
#include <raymath.h>

#include "CardSet.h"


// piles hold any number of cards
typedef struct Pile {
    Card pile[MAX_CARDS];
    Card top;
    Card bottom;
    Rectangle rect;
    int size;
    bool is_faceup;
} Pile;

// slots hold 1 card
typedef struct Slot {
    Card card;
    Card card_back;
    Rectangle rect;
    bool is_faceup;
} Slot;


Pile *init_pile(Vector2 pile_pos, CardSet *card_set);
void update_pile(Pile *pile);
void draw_pile(Pile *pile);
void destroy_pile(Pile *pile);

void push_card_to_pile(Pile *pile, Card *card);
Card pop_card_from_pile(Pile *pile);
void shuffle_pile(Pile *pile);


Slot *init_slot(Vector2 slot_pos, CardSet *card_set);
void update_slot(Slot *slot);
void draw_slot(Slot *slot);
void destroy_slot(Slot *slot);

void put_card_in_slot(Slot *slot, Card *card);
Card take_card_from_slot(Slot *slot);
