#ifndef HUD_H
#define HUD_H

#include <gb/gb.h>
#include <stdint.h>

void hud_init(void);
void hud_default(void);
void hud_update_score(uint8_t score, uint8_t goal);
void hud_uint_to_hex(uint8_t number, char zero_hex_value_reference, uint8_t out_hex[2]);

#endif