#include "scoundrel_scene.h"

#include <raylib.h>
#include <raymath.h>
#include <stdbool.h>
#include <stdlib.h>

#include "CardSet.h"
#include "LooseCard.h"
#include "Pile.h"


typedef enum PHASE_STATE {
    DRAW_PHASE,
    KEEP_PHASE,
    MAIN_PHASE,

    PHASES_NUM,
} PHASE_STATE;

typedef enum SCOUNDREL_CARD_TYPE {
    HEALTH_POTION_TYPE = HEARTS_SUIT,
    WEAPON_TYPE = DIAMONDS_SUIT,
    MONSTER_CLUB_TYPE = CLUBS_SUIT,
    MONSTER_SPADE_TYPE = SPADES_SUIT,
} SCOUNDREL_CARD_TYPE;


#define ROOM_SIZE 4
#define NEW_CARD_TIME .5f
#define MAX_LIFE 20
#define ACE_CARD_VALUE_MODIFIER 14
#define CARD_VALUE_MODIFIER 1


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
static PHASE_STATE current_phase = 0;
static bool is_room_avoidable = true;


static Pile *_init_scoundrel_deck(CardSet *card_set, Vector2 deck_pos);
static void _draw_scoundrel_deck(Pile *deck_dungeon);
static void _destroy_soundrel_deck(Pile *deck_dungeon);
static void _fill_room(float dt);
static void _update_all_cards(float dt);
static void _update_room(float dt);
static void _update_card_in_room(Slot *room);
static void _avoid_room(void);
static void _update_scoundrel_card(Card *card, float dt);

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
        .x=deck_rect.x+(deck_rect.width*3)+3,
        .y=deck_rect.y*2,
    };
    weapon_slot = init_slot(weapon_pos, card_set);
    life_points = MAX_LIFE;

    is_room_avoidable = true;
    current_phase = DRAW_PHASE;

    return;
}
void update_scoundrel(float dt) {
    _update_room(dt);
    if (IsKeyPressed(KEY_N)) {
        for (int i=0; i<MAX_CARDS; i++) {
            if (card_list[i].is_active) {
                continue;
            }
            card_list[i] = instance_card(card_set, DIAMONDS_SUIT, KING_NUM, GetMousePosition());
            break;
        }
    }
    _update_all_cards(dt);

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

    Vector2 life_pos = {
        .x=weapon_slot->rect.x + weapon_slot->rect.width + 5,
        .y=discard_pile->rect.y*2+5,
    };
    DrawText(TextFormat("LP: %i", life_points), life_pos.x, life_pos.y, 30, WHITE);
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
void _fill_room(float dt) {
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
    if (!is_room_to_be_filled) {
        if (is_room_avoidable && empty_rooms == 0) {
            current_phase = KEEP_PHASE;
            is_room_avoidable = false;
        } else {
            current_phase = MAIN_PHASE;
            is_room_avoidable = true;
        }
    }

    return;
}
void _update_all_cards(float dt) {
    for (int i=0; i<MAX_CARDS; i++) {
        if (!card_list[i].is_active) {
            continue;
        }
        Vector2 discard_pile_placement = (Vector2) {
            .x=discard_pile->rect.x, .y=discard_pile->rect.y
        };
        Vector2 card_pos = { card_list[i].spr.dest_rec.x, card_list[i].spr.dest_rec.y };
        bool is_card_in_place = (
            Vector2Distance(card_pos, card_list[i].placement) < 1.f &&
            !card_list[i].is_pickup
        );
        for (int j=0; j<ROOM_SIZE; j++) {
            if (!is_card_in_place) {
                continue;
            }
            if (CheckCollisionRecs(card_list[i].spr.dest_rec, dungeon_room[j].rect)) {
                put_card_in_slot(&dungeon_room[j], &card_list[i]);
            }
        }
        if (is_card_in_place && card_list[i].suit == (CARD_SUIT) WEAPON_TYPE) {
            if (CheckCollisionRecs(card_list[i].spr.dest_rec, weapon_slot->rect)) {
                if (weapon_slot->card.is_active) {
                    for (int j=0; j<MAX_CARDS; j++) {
                        if (card_list[j].is_active) {
                            continue;
                        }
                        card_list[j] = take_card_from_slot(weapon_slot);
                        card_list[j].placement = discard_pile_placement;
                        card_list[j].spr.dest_rec.y -= card_list[j].spr.dest_rec.height;
                        break;
                    }
                }
                put_card_in_slot(weapon_slot, &card_list[i]);
                current_phase = DRAW_PHASE;
            }
        }

        bool is_in_weapon = CheckCollisionRecs(card_list[i].spr.dest_rec, weapon_slot->rect);
        bool is_loose = !card_list[i].is_pickup;
        bool is_discarted = Vector2Equals(card_list[i].placement, discard_pile_placement);

        bool is_monster_type = (bool) (
            card_list[i].suit == (CARD_SUIT) MONSTER_CLUB_TYPE ||
            card_list[i].suit == (CARD_SUIT) MONSTER_SPADE_TYPE
        );
        bool is_taking_damage = is_monster_type && is_in_weapon && is_loose && !is_discarted;
        if (is_taking_damage) {
            if (!weapon_slot->card.is_active) {
                if (card_list[i].num == ACE_NUM) {
                    life_points -= card_list[i].num + ACE_CARD_VALUE_MODIFIER;
                } else {
                    life_points -= card_list[i].num + CARD_VALUE_MODIFIER;
                }
            }
            card_list[i].placement = discard_pile_placement;
        }

        bool is_potion_type = card_list[i].suit == (CARD_SUIT) HEALTH_POTION_TYPE;
        bool is_healing_damage = is_potion_type && is_in_weapon && is_loose && !is_discarted;
        if (is_healing_damage) {
            if (card_list[i].num == ACE_NUM) {
                life_points += card_list[i].num + ACE_CARD_VALUE_MODIFIER;
            } else {
                life_points += card_list[i].num + CARD_VALUE_MODIFIER;
            }
            card_list[i].placement = discard_pile_placement;
        }

        if (is_discarted) {
            if (is_card_in_place) {
                push_card_to_pile(discard_pile, &card_list[i]);
                current_phase = DRAW_PHASE;
            }
        }
        _update_scoundrel_card(&card_list[i], dt);
    }

    return;
}
void _update_room(float dt) {
    switch (current_phase) {
        case DRAW_PHASE:
            _fill_room(dt);
            break;

        case KEEP_PHASE:
            if (IsKeyPressed(KEY_F)) {
                current_phase = MAIN_PHASE;
            }
            if (IsKeyPressed(KEY_A)) {
                _avoid_room();
            }
            break;

        case MAIN_PHASE:
            for (int i=0; i<ROOM_SIZE; i++) {
                if (!dungeon_room[i].card.is_active) {
                    continue;
                }
                _update_card_in_room(&dungeon_room[i]);
            }
            break;

        case PHASES_NUM:
            break;
    }

    return;
}
void _update_card_in_room(Slot *room) {
    bool is_collision_mouse_slot = CheckCollisionPointRec(GetMousePosition(), room->rect);
    bool is_left_mouse_pressed = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

    bool is_slot_clicked = is_left_mouse_pressed && is_collision_mouse_slot;

    if (is_slot_clicked) {
        for (int j=0; j<MAX_CARDS; j++) {
            if (card_list[j].is_active) {
                continue;
            } else {
                card_list[j] = take_card_from_slot(room);
                card_list[j].is_pickup = true;

                break;
            }
        }
    }
}
void _avoid_room(void) {
    Pile temp = {0};
    for (int i=0; i<MAX_CARDS; i++) {
        if (i-ROOM_SIZE >= deck_dungeon->size) { break; }
        if (i<ROOM_SIZE) {
            temp.pile[i] = dungeon_room[i].card;
            take_card_from_slot(&dungeon_room[i]);
            continue;
        }
        temp.pile[i] = deck_dungeon->pile[i-ROOM_SIZE];
    }
    for (int i=0; i<MAX_CARDS; i++) {
        if (i-ROOM_SIZE >= deck_dungeon->size) { break; }
        deck_dungeon->pile[i] = temp.pile[i];
    }
    deck_dungeon->size += ROOM_SIZE;

    current_phase = DRAW_PHASE;
    is_room_avoidable = false;
}
void _update_scoundrel_card(Card *card, float dt) {
    if (current_phase == MAIN_PHASE) {
        pickup_card(card);

        if (!card->is_pickup && card->suit == (CARD_SUIT) WEAPON_TYPE) {
            if (CheckCollisionRecs(card->spr.dest_rec, weapon_slot->rect)) {
                card->placement = (Vector2) {
                    .x=weapon_slot->rect.x,
                    .y=weapon_slot->rect.y,
                };
            }
        }
    }
    move_card_to_placement(card, dt);

    return;
}
