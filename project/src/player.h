#ifndef PLAYER_H
#define PLAYER_H

#include <gb/gb.h>
#include <stdint.h>
#include <stdbool.h>

#define PLAYER_SPEED 2
#define PLAYER_WIDTH 8
#define PLAYER_HEIGHT 8
#define PLAYER_SPRITE_START 26

typedef enum {
    PLAYER_IDLE,
    PLAYER_WALKING,
    PLAYER_JUMPING
} PlayerState;

typedef enum {
    DIR_RIGHT = 0,
    DIR_LEFT = 1,
    DIR_UP = 2,
    DIR_DOWN = 3
} Direction;

typedef struct {
    uint8_t x;
    uint8_t y;
    uint8_t sprite_index;
    uint8_t score;
    uint8_t health;
    uint8_t invincible_timer;
    BOOLEAN is_invincible;
    Direction direction;
    PlayerState state;
} Player;

void player_init(Player* player, uint8_t x, uint8_t y);
void player_update(Player* player);
void player_render(Player* player);
void player_take_damage(Player* player, uint8_t damage);
void player_add_score (Player* player, uint8_t points);

uint8_t player_get_left(Player* player);
uint8_t player_get_right(Player* player);
uint8_t player_get_top(Player* player);
uint8_t player_get_bottom(Player* player);

#endif