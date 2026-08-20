#include "scoundrel_scene.h"

#include <raylib.h>
#include <raymath.h>
#include <stdbool.h>
#include <stdlib.h>

#include "CardSet.h"
#include "CardLose.h"
#include "Pile.h"


typedef enum SCOUNDREL_CARD_TYPE {
    HEALTH_POTION_TYPE = HEARTS_SUIT,
    WEAPON_TYPE = DIAMONDS_SUIT,
    MONSTER_CLUB_TYPE = CLUBS_SUIT,
    MONSTER_SPADE_TYPE = SPADES_SUIT,
} SCOUNDREL_CARD_TYPE;

typedef enum SCOUNDREL_CARD_VALUE {
    TWO_VALUE = 2,
    THREE_VALUE,
    FOUR_VALUE,
    FIVE_VALUE,
    SIX_VALUE,
    SEVEN_VALUE,
    EIGHT_VALUE,
    NINE_VALUE,
    TEN_VALUE,
    JACK_VALUE,
    QUEEN_VALUE,
    KING_VALUE,
    ACE_VALUE,
} SCOUNDREL_CARD_VALUE;


#define ROOM_SIZE 4
#define NEW_CARD_TIME .5f
#define MAX_LIFE 20


static Card card_list[MAX_CARDS] = {0};
static CardSet *card_set = NULL;
static Pile *discard_pile = NULL;
static Pile *deck_dungeon = NULL;
static Slot dungeon_room[ROOM_SIZE] = {0};
static Slot *weapon_slot = NULL;
static float new_card_timer = NEW_CARD_TIME;
static bool is_room_to_be_filled = false;
static Vector2 empty_room_slots[ROOM_SIZE] = {0};
static int life_points = 0;


static Pile *_init_scoundrel_deck(CardSet *card_set, Vector2 deck_pos);
static void _draw_scoundrel_deck(Pile *deck_dungeon);
static void _destroy_soundrel_deck(Pile *deck_dungeon);

void init_scoundrel(CardSet *resources_card_set){
    card_set = resources_card_set;

    deck_dungeon = _init_scoundrel_deck(card_set, (Vector2) { .x=200, .y=150 });

    Rectangle deck_rect = deck_dungeon->rect;

    Vector2 discard_pile_pos = { .x=deck_rect.x+9+deck_rect.width*7, .y=deck_rect.y };
    discard_pile = init_pile(discard_pile_pos, card_set);

    Vector2 room_pos = { .x=deck_rect.x+deck_rect.width*2, .y=deck_rect.y };
    for (int i=0; i<ROOM_SIZE; i++) {
        dungeon_room[i] = *init_slot(room_pos, card_set);
        room_pos.x +=deck_rect.width+3;
    }

    Vector2 weapon_pos = {
        .x=deck_rect.x+(discard_pile_pos.x-deck_rect.x)/2,
        .y=deck_rect.y*2,
    };
    weapon_slot = init_slot(weapon_pos, card_set);
    life_points = MAX_LIFE;

    return;
}
void update_scoundrel(float dt) {
    int empty_rooms = 0;
    for (int i=0; i<ROOM_SIZE; i++) {
        if (!dungeon_room[i].card.is_active) {
            empty_rooms++;
            if (!is_room_to_be_filled) {
                empty_room_slots[i].x = dungeon_room[i].rect.x;
                empty_room_slots[i].y = dungeon_room[i].rect.y;
            }
        }
    }
    if (empty_rooms > 2) {
        is_room_to_be_filled = true;
    }
    if (is_room_to_be_filled) {
        new_card_timer -= dt;
    }
    if (new_card_timer <= 0) {
        new_card_timer = NEW_CARD_TIME;
        for (int i=0; i<MAX_CARDS; i++) {
            if (card_list[i].is_active) {
                continue;
            }
            card_list[i] = pop_card_from_pile(deck_dungeon);
            for (int j=0; j<ROOM_SIZE; j++) {
                if (Vector2Equals(empty_room_slots[j], Vector2Zero())) {
                    continue;
                } else {
                    card_list[i].placement = empty_room_slots[j];
                    empty_room_slots[j] = Vector2Zero();
                    break;
                }
            }
            break;
        }
    }
    if (empty_rooms == 0) {
        is_room_to_be_filled = false;
    }

    for (int i=0; i<MAX_CARDS; i++) {
        if (!card_list[i].is_active) {
            continue;
        }
        Vector2 card_pos = { card_list[i].spr.dest_rec.x, card_list[i].spr.dest_rec.y };
        for (int j=0; j<ROOM_SIZE; j++) {
            if (Vector2Distance(card_pos, card_list[i].placement) > 1.f || card_list[i].is_pickup) {
                continue;
            }
            if (CheckCollisionRecs(card_list[i].spr.dest_rec, dungeon_room[j].rect)) {
                put_card_in_slot(&dungeon_room[j], &card_list[i]);
            }
        }
        update_card(&card_list[i], dt);
    }

    return;
}
void draw_scoundrel(void) {
    ClearBackground(SKYBLUE);
    DrawFPS(10, 10);

    _draw_scoundrel_deck(deck_dungeon);
    draw_pile(discard_pile);

    for (int i=0; i<ROOM_SIZE; i++) {
        draw_slot(&dungeon_room[i]);
    }

    draw_slot(weapon_slot);

    for (int i=0; i<MAX_CARDS; i++) {
        draw_card(&card_list[i]);
    }
}
void destroy_scoundrel(void) {
    _destroy_soundrel_deck(deck_dungeon);
    destroy_pile(discard_pile);
    destroy_slot(weapon_slot);

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
