#ifndef HUD_H
#define HUD_H

#include <gb/gb.h>
#include <stdint.h>

void hud_init(void);
void hud_default(void);
void hud_update_score(uint16_t score);

#endif