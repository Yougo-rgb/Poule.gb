#include "audio.h"

static BOOLEAN sound_playing = FALSE;
static uint8_t sound_timer = 0;

void audio_init(void) {
    NR52_REG = 0x80;
    NR50_REG = 0x77;
    NR51_REG = 0xFF;
}

void audio_play_sfx(SoundEffect sfx) {
    switch(sfx) {
        case SFX_MOVE:
            NR10_REG = 0b00010110;
            NR11_REG = 0b00011000;
            NR12_REG = 0b01110011;
            NR13_REG = 0b00000000;
            NR14_REG = 0b11000011;
            sound_timer = 5;
            break;
    }
}

void audio_stop_all(void) {
    NR12_REG = 0x00;
    NR14_REG = 0x00;
    NR42_REG = 0x00;
    sound_playing = FALSE;
    sound_timer = 0;
}

bool audio_is_playing(void) {
    if(sound_timer > 0) {
        sound_timer--;
        if(sound_timer == 0) {
            sound_playing = FALSE;
        }
    }
    return sound_playing;
}