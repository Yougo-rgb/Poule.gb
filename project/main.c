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

Player player;
ItemManager item_manager;

void on_item_collected(ItemType type, uint8_t value, uint8_t item_index) {
    switch(type) {
        case ITEM_EGG:
            player_add_score(&player, value);
            /* audio_play_sfx(...) */
            item_remove(&item_manager, item_index);
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
    item_spawn(&item_manager, 40, 64, ITEM_EGG, 1);

    SHOW_BKG;
    SHOW_SPRITES;  
    SHOW_WIN;  
    DISPLAY_ON;
}

void new_rand_egg(void) {
    // TODO
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

    while(1){
        update_game();
        render_game();

        vsync();
    }

}