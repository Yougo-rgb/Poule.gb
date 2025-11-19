#include <gb/gb.h>
#include <stdio.h>
#include <stdint.h>

#include "src/audio.h"
#include "src/player.h"
#include "./assets/Background.c"
#include "./assets/BackgroundTile.c"
//#include "./assets/Character.c"
#include "./assets/ChickenLittle.c"
#include "./assets/EggLittle.c"

Player player;

void init_game() {
    
    audio_init();
    
    set_bkg_data(0, 11, backTile);
    set_bkg_submap(0, 0, 20, 18, backMap, 20);
    
    set_sprite_data(0, 4, chickenLittleSprite);

    player_init(&player, 88, 80);
    
    SHOW_BKG;
    SHOW_SPRITES;    
    DISPLAY_ON;
}

void update_game() {
    player_update(&player);
}

void render_game() {
    player_render(&player);
}

void main() {
    init_game();

    while(1){
        update_game();
        render_game();

        vsync();
    }

}