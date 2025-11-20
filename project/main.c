#include <gb/gb.h>
#include <stdio.h>
#include <stdint.h>

#include "src/hud.h"
#include "src/audio.h"
#include "src/player.h"
#include "./assets/Background.c"
#include "./assets/BackgroundTile.c"
//#include "./assets/Character.c"
#include "./assets/ChickenLittle.c"
#include "./assets/EggLittle.c"

Player player;

void init_game(void) {
    
    audio_init();
    hud_init();
    
    set_bkg_data(38, 11, backTile);
    set_bkg_submap(0, 0, 20, 18, backMap, 20);
    
    set_sprite_data(0, 4, chickenLittleSprite);


    player_init(&player, 88, 80);
    
    SHOW_BKG;
    SHOW_SPRITES;  
    SHOW_WIN;  
    DISPLAY_ON;
}

void update_game(void) {
    player_update(&player);
}

void render_game(void) {
    player_render(&player);
}

void main(void) {
    init_game();

    while(1){
        update_game();
        render_game();

        vsync();
    }

}