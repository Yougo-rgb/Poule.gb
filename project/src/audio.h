#ifndef AUDIO_H
#define AUDIO_H

#include <gb/gb.h>
#include <stdint.h>
#include <stdbool.h>

typedef enum {
    SFX_MOVE
    // add more sfx in the futur
} SoundEffect;

void audio_init(void);
void audio_play_sfx(SoundEffect sfx);
void audio_stop_all(void);
bool audio_is_playing(void);

#endif