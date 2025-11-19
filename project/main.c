#include <gb/gb.h>
#include <stdio.h>
#include <stdint.h>

#include "src/audio.c"
#include "./assets/Background.c"
#include "./assets/BackgroundTile.c"
//#include "./assets/Character.c"
#include "./assets/ChickenLittle.c"
#include "./assets/EggLittle.c"

//constant
#define PLAYER_SPEED 2
#define SCREEN_MIN_X 8
#define SCREEN_MAX_X 160
#define SCREEN_MIN_Y 16
#define SCREEN_MAX_Y 152

void main(){
    
    uint8_t sprite_x = 88;
    uint8_t sprite_y = 80;
    uint8_t current_sprite_index = 0;
    BOOLEAN can_play_sound = TRUE;

    audio_init();

    set_bkg_data(0, 11, backTile);
    set_bkg_submap(0, 0, 20, 18, backMap, 20);
    
    set_sprite_data(0, 4, chickenLittleSprite);
    set_sprite_tile(0, current_sprite_index);
    move_sprite(0, sprite_x, sprite_y);

    SHOW_BKG;
    SHOW_SPRITES;    
    DISPLAY_ON;

    while(1){
        UBYTE joypad_state = joypad();
        BOOLEAN moved = FALSE;

        if(joypad_state & J_LEFT && sprite_x > SCREEN_MIN_X) {
            current_sprite_index = 1;
            sprite_x -= PLAYER_SPEED;
            moved = TRUE;
        }
        if(joypad_state & J_RIGHT && sprite_x < SCREEN_MAX_X) {
            current_sprite_index = 0;
            sprite_x += PLAYER_SPEED;
            moved = TRUE;
        }
        if(joypad_state & J_UP && sprite_y > SCREEN_MIN_Y) {
            current_sprite_index = 0;
            sprite_y -= PLAYER_SPEED;
            moved = TRUE;
        }
        if(joypad_state & J_DOWN && sprite_y < SCREEN_MAX_Y) {
            current_sprite_index = 3;
            sprite_y += PLAYER_SPEED;
            moved = TRUE;
        }

        if (moved && can_play_sound) {
            audio_play_sfx(SFX_MOVE);
            can_play_sound = FALSE;
        } else if (joypad_state == 0) {
            can_play_sound = TRUE;
        }

        move_sprite(0, sprite_x, sprite_y);
        set_sprite_tile(0, current_sprite_index);

        vsync();
    }

}