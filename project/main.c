#include <gb/gb.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <rand.h>

#include "src/hud.h"
#include "src/audio.h"
#include "src/player.h"
#include "src/item.h"

// #include "./assets/Background.c"
#include "./assets/CompBackground.c"
#include "./assets/BackgroundTile.c"
// #include "./assets/Character.c"
#include "./assets/ChickenLittle.c"
#include "./assets/EggLittle.c"
#include "./assets/CustomFont.c"

#define SCREEN_MIN_X 24
#define SCREEN_MAX_X 152
#define SCREEN_MIN_Y 56
#define SCREEN_MAX_Y 128

typedef struct {
    uint8_t collected;
    uint32_t frame_started;
    uint32_t frame_collected;
} GameObject;

Player player;
ItemManager item_manager;
UBYTE x, y;
UWORD seed;
BOOLEAN is_game_playing;
uint8_t goal_score;
unsigned char decompressed_map[360];
uint32_t frames_elapsed = 0;
GameObject time;

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

uint32_t calculed_time_score(void) {
    uint32_t seconds = time.frame_collected / 60;
    return seconds;
}

void decompress_map(DataPoint arr[], int arr_size) {
    int map_index = 0;
    for (int i = 0; i < arr_size; i++) {
        unsigned char value = arr[i].value;
        int count = arr[i].count;

        for (int j = 0; j < count; j++) {
            if (map_index < arr_size) {
                decompressed_map[map_index++] = value;
            } else {
                break;
            }
        }
    }
}

void init_game(void) {

    audio_init();
    hud_init();
    
    set_bkg_data(38, 11, backTile);

    decompress_map(dataList, 360);

    set_bkg_submap(0, 0, 20, 18, decompressed_map, 20);
    
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
    goal_score = 50;
    time.frame_started = frames_elapsed;  
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
    printf("\n"); // TODO: Create a real interface
    while(1) {
        if (is_game_playing) {
            update_game();
            render_game();
            if (player.score >= goal_score) {
                time.frame_collected = frames_elapsed - time.frame_started;
                fill_bkg_rect(0, 1, 31, 1, 0); // TODO: Create a real interface
                printf("%d",calculed_time_score()); // TODO: Create a real interface
                waitpad(0xFF);
                waitpadup();
                is_game_playing= FALSE;
            } 
        } else {
            reset_game();
            waitpad(0xFF);
            start_game();
        }
        wait_vbl_done();
        frames_elapsed++;
    }

}