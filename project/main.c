#include <gb/gb.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <rand.h>

#include "src/hud.h"
#include "src/audio.h"
#include "src/player.h"
#include "src/item.h"

#include "./assets/Background.c"
#include "./assets/BackgroundTile.c"
//#include "./assets/Character.c"
#include "./assets/ChickenLittle.c"
#include "./assets/EggLittle.c"
#include "./assets/CustomFont.c"

#define SCREEN_MIN_X 24
#define SCREEN_MAX_X 152
#define SCREEN_MIN_Y 56
#define SCREEN_MAX_Y 128

Player player;
ItemManager item_manager;
UBYTE x, y;
UWORD seed;
BOOLEAN is_game_playing;
uint8_t goal_score;

void new_rand_x_y_pos(void) {
    seed = DIV_REG;
    initarand(seed);
    x = rand();
    y = arand();
}

void new_rand_egg( UBYTE x, UBYTE y) {
    item_spawn(&item_manager, x, y, ITEM_EGG, 1);
}

void on_item_collected(ItemType type, uint8_t value, uint8_t item_index) {
    switch(type) {
        case ITEM_EGG:
            player_add_score(&player, value);
            hud_update_score(player.score, goal_score);
            /* audio_play_sfx(...) */
            item_remove(&item_manager, item_index);

            new_rand_x_y_pos();
            x = x % (SCREEN_MAX_X - SCREEN_MIN_X);
            y = y % (SCREEN_MAX_Y - SCREEN_MIN_Y);
            new_rand_egg(x + SCREEN_MIN_X, y + SCREEN_MIN_Y);
            break;
        default:
            break;
    }
}

void init_game(void) {

    audio_init();
    hud_init();
    
    set_bkg_data(38, 11, backTile);
    set_bkg_submap(0, 0, 20, 18, backMap, 20);
    
    set_sprite_data(0, 4, chickenLittleSprite);
    player_init(&player, 88, 80);
    
    set_sprite_data(4, 4, EggLittleSprite);
    item_manager_init(&item_manager);

    set_bkg_data(53, 8, CustomFont);

    SHOW_BKG;
    SHOW_SPRITES;  
    SHOW_WIN;  
    DISPLAY_ON;
}

void reset_game(void) { 
    is_game_playing = FALSE;
    item_manager_init(&item_manager);
    hud_default();
}

void start_game(void) {
    is_game_playing = TRUE;

    hud_default();
    player_init(&player, 88, 80);

    new_rand_x_y_pos();
    x = x % (SCREEN_MAX_X - SCREEN_MIN_X);
    y = y % (SCREEN_MAX_Y - SCREEN_MIN_Y);
    goal_score = (x % 10) + 5;
    new_rand_egg(x + SCREEN_MIN_X, y + SCREEN_MIN_Y);
}

void update_game(void) {
    player_update(&player);
    item_update(&item_manager);

    item_check_collision(
        &item_manager,
        player.x,
        player.y,
        PLAYER_WIDTH,
        PLAYER_HEIGHT,
        on_item_collected
    );
}

void render_game(void) {
    player_render(&player);
    item_render(&item_manager);
}

void main(void) {
    init_game();
    waitpad(0xFF);
    waitpadup();
    while(1) {
        if (is_game_playing) {
            update_game();
            render_game();
            if (player.score >= goal_score) {
                is_game_playing= FALSE;
            } 
            vsync();
        } else {
            reset_game();
            waitpad(0xFF);
            start_game();
        }
    }

}