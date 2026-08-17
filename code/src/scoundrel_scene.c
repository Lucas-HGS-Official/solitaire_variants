#include "scoundrel_scene.h"

#include <raylib.h>
#include <stdbool.h>
#include <stdlib.h>

#include "CardSet.h"
#include "CardLose.h"
#include "Pile.h"


static Card card_list[MAX_CARDS] = {0};
static CardSet *card_set = NULL;
static Pile *discard_pile = NULL;
static Pile *deck_dungeon = NULL;
static Slot *test_slot = NULL;


static Pile *_init_scoundrel_deck(CardSet *card_set, Vector2 deck_pos);
static void _draw_scoundrel_deck(Pile *deck_dungeon);
static void _destroy_soundrel_deck(Pile *deck_dungeon);

void init_scoundrel(CardSet *resources_card_set){
    card_set = resources_card_set;

    deck_dungeon = _init_scoundrel_deck(card_set, (Vector2) { 200, 150 });

    return;
}
void update_scoundrel(float dt) {
    return;
}
void draw_scoundrel(void) {
    ClearBackground(SKYBLUE);
    DrawFPS(10, 10);

    _draw_scoundrel_deck(deck_dungeon);
}
void destroy_scoundrel(void) {
    _destroy_soundrel_deck(deck_dungeon);

    return;
}


static Pile *_init_scoundrel_deck(CardSet *card_set, Vector2 deck_pos) {
    Pile *new_deck;
    new_deck = init_pile(deck_pos, card_set);
    new_deck->is_faceup = false;

    for (int i=0; i<DECK_SIZE; i++) {
        if (
            (card_set->cards[i].suit == HEARTS_SUIT ||
            card_set->cards[i].suit == DIAMONDS_SUIT) &&
            (card_set->cards[i].num > TEN_NUM ||
            card_set->cards[i].num == ACE_NUM)
        ) {
            continue;
        }
        Card card_to_push = card_set->cards[i];
        push_card_to_pile(new_deck, &card_to_push);
    }
    shuffle_pile(new_deck);

    return new_deck;
}
void _draw_scoundrel_deck(Pile *deck_dungeon) {
    draw_pile(deck_dungeon);

    return;
}
void _destroy_soundrel_deck(Pile *deck_dungeon) {
    destroy_pile(deck_dungeon);

    return;
}
