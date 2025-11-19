#include "player.h"
#include "audio.h"

#define SCREEN_MIN_X 24
#define SCREEN_MAX_X 152
#define SCREEN_MIN_Y 56
#define SCREEN_MAX_Y 128

#define BLINK_DURATION 60
static uint8_t blink_counter = 0;

void player_init(Player* player, uint8_t x, uint8_t y) {
    player->x = x;
    player->y = y;
    player->sprite_index = DIR_RIGHT;
    player->direction = DIR_RIGHT;
    player->state = PLAYER_IDLE;
    player->health = 3;
    player->score = 0;
    player->invincible_timer = 0;
    player->is_invincible = FALSE;
}

void player_update(Player* player) {
    uint8_t joypad_state = joypad();
    bool moved = false;

    if (player->is_invincible) {
        player->is_invincible--;
        if (player->invincible_timer == 0) {
            player-> is_invincible = FALSE;
        }
    }

    if (joypad_state & J_LEFT && player->x > SCREEN_MIN_X) {
        player->x -= PLAYER_SPEED;
        player->direction = DIR_LEFT;
        player->sprite_index = DIR_LEFT;
        moved = true;
    }

    if (joypad_state & J_RIGHT && player->x < SCREEN_MAX_X - PLAYER_WIDTH) {
        player->x += PLAYER_SPEED;
        player->direction = DIR_RIGHT;
        player->sprite_index = DIR_RIGHT;
        moved = true;
    }

    if (joypad_state & J_UP && player->y > SCREEN_MIN_Y) {
        player->y -= PLAYER_SPEED;
        player->direction = DIR_UP;
        player->sprite_index = DIR_RIGHT;
        moved = true;
    }

    if (joypad_state & J_DOWN && player->y < SCREEN_MAX_Y - PLAYER_HEIGHT) {
        player->y += PLAYER_SPEED;
        player->direction = DIR_DOWN;
        player->sprite_index = DIR_DOWN;
        moved = true;
    }

    if(moved) {
        player->state = PLAYER_WALKING;
        static uint8_t step_counter = 0;
        step_counter++;
        if(step_counter > 15) {
            audio_play_sfx(SFX_MOVE);
            step_counter = 0;
        }
    } else {
        player->state = PLAYER_IDLE;
    }
}

void player_render(Player* player) {
    // Add if statement to make flaching effect when invincible

    move_sprite(PLAYER_SPRITE_START, player->x, player->y);
    set_sprite_tile(PLAYER_SPRITE_START, player->sprite_index);
}

void player_take_damage(Player* player, uint8_t damage) {
    if(player->is_invincible) return;

    if (player->health > damage) {
        player->health -= damage;
    } else {
        player-> health = 0;
    }

    player->is_invincible = true;
    player->invincible_timer = BLINK_DURATION;
}

void player_add_score(Player* player, uint8_t points) {
    player->score += points;

    /* audio_play_sfx(...) */
}

uint8_t player_get_left(Player* player) {
    return player->x;
}

uint8_t player_get_right(Player* player) {
    return player->x + PLAYER_WIDTH;
}

uint8_t player_get_top(Player* player) {
    return player->y;
}

uint8_t player_get_bottom(Player* player) {
    return player->y + PLAYER_HEIGHT;
}