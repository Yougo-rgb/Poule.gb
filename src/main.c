#include <gb/gb.h>
#include <stdio.h>
#include <stdint.h>

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

void init_audio(){
    NR52_REG = 0x80;
    NR50_REG = 0x77;
    NR51_REG = 0xFF;
}

void play_move_sound() {
    // see https://github.com/bwhitman/pushpin/blob/master/src/gbsound.txt
    // chanel 1 register 0, Frequency sweep settings
    // 7	Unused
    // 6-4	Sweep time(update rate) (if 0, sweeping is off)
    // 3	Sweep Direction (1: decrease, 0: increase)
    // 2-0	Sweep RtShift amount (if 0, sweeping is off)
    NR10_REG = 0b00010110;

    // chanel 1 register 1: Wave pattern duty and sound length
    // Channels 1 2 and 4
    // 7-6	Wave pattern duty cycle 0-3 (12.5%, 25%, 50%, 75%), duty cycle is how long a quadrangular  wave is "on" vs "of" so 50% (2) is both equal.
    // 5-0 sound length (higher the number shorter the sound)
    NR11_REG = 0b00011000;

    // chanel 1 register 2: Volume Envelope (Makes the volume get louder or quieter each "tick")
    // On Channels 1 2 and 4
    // 7-4	(Initial) Channel Volume
    // 3	Volume sweep direction (0: down; 1: up)
    // 2-0	Length of each step in sweep (if 0, sweeping is off)
    // NOTE: each step is n/64 seconds long, where n is 1-7	
    NR12_REG = 0b01110011;

    // chanel 1 register 3: Frequency LSbs (Least Significant bits) and noise options
    // for Channels 1 2 and 3
    // 7-0	8 Least Significant bits of frequency (3 Most Significant Bits are set in register 4)
    NR13_REG = 0b00000000;

    // chanel 1 register 4: Playback and frequency MSbs
    // Channels 1 2 3 and 4
    // 7	Initialize (trigger channel start, AKA channel INIT) (Write only)
    // 6	Consecutive select/length counter enable (Read/Write). When "0", regardless of the length of data on the NR11 register, sound can be produced consecutively.  When "1", sound is generated during the time period set by the length data contained in register NR11.  After the sound is ouput, the Sound 1 ON flag, at bit 0 of register NR52 is reset.
    // 5-3	Unused
    // 2-0	3 Most Significant bits of frequency
    NR14_REG = 0b11000011;
}

void main(){
    
    uint8_t sprite_x = 88;
    uint8_t sprite_y = 80;
    uint8_t current_sprite_index = 0;
    BOOLEAN can_play_sound = TRUE;

    init_audio();
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
            play_move_sound();
            can_play_sound = FALSE;
        } else if (joypad_state == 0) {
            can_play_sound = TRUE;
        }

        move_sprite(0, sprite_x, sprite_y);
        set_sprite_tile(0, current_sprite_index);

        vsync();
    }

}