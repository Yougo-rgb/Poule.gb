#include "hud.h"
#include <gbdk/font.h>
#include <stdio.h>
#include <gb/gb.h>

void hud_uint_to_hex(uint16_t number, char zero_hex_value_reference, uint8_t out_hex[2]);

unsigned char windowmap[] = {
    0x00,0x00,0x00, 0x1D, 0x1E, 0x0B, 0x1C, 0x1E, 0x00, 0x1A, 0x19, 0x1F, 0x16, 0x0F, 0x00, 0x11, 0x0C, 0x00,0x00,0x00
};

static font_t min_font;

void lcd_isr(void) {
    while(STAT_REG & 0x03);
    HIDE_WIN;
}

void vbl_isr(void) {
    SHOW_WIN;
}

void hud_init(void) {
    font_init();
    min_font = font_load(font_min);
    font_set(min_font);

    set_win_tiles(0, 0, 20, 1, windowmap);
    move_win(7, 0);

    STAT_REG = 0x40;
    LYC_REG = 0x08;

    disable_interrupts();
    add_LCD(lcd_isr);
    add_LCD(wait_int_handler);
    add_VBL(vbl_isr);
    enable_interrupts();
    set_interrupts(VBL_IFLAG | LCD_IFLAG);
}

void hud_default(void) {
    unsigned char windowmap[] = {
        0x00,0x00,0x00,0x00, 0x1A, 0x19, 0x1F, 0x16, 0x0F, 0x00, 0x11, 0x0C, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00,0x00
    };
    set_win_tiles(0, 0, 20, 1, windowmap);
    move_win(7, 0);
}

void hud_update_score(uint16_t score) {
	uint8_t score_hex[2];
	
	hud_uint_to_hex(score, 1, score_hex);
	
    unsigned char windowmap[] = {
        0x00,0x00,0x00,0x00, 0x1A, 0x19, 0x1F, 0x16, 0x0F, 0x00, 0x11, 0x0C, 0x00, 0x00, score_hex[0], score_hex[1], 0x00, 0x00, 0x00,0x00
    };
    set_win_tiles(0, 0, 20, 1, windowmap);
    move_win(7, 0);
}

void hud_uint_to_hex(uint16_t number, char zero_hex_value_reference, uint8_t out_hex[2]) {

    uint8_t unit_digit = number % 10;
    uint8_t decimal_digit = (number / 10) % 10;

    uint8_t digits[2] = { decimal_digit, unit_digit };

    for (int i = 0; i < 2; i++) {
        out_hex[i] = digits[i] + zero_hex_value_reference;
    }
}