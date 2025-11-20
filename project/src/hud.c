#include "hud.h"
#include <gbdk/font.h>
#include <stdio.h>
#include <gb/gb.h>

unsigned char windowmap[] = {
    0x1A, 0x19, 0x1F, 0x16, 0x0F, 0x00, 0x11, 0x0C
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

    set_win_tiles(0, 0, 8, 1, windowmap);
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

void hud_update_score(uint16_t score) {
    // 
}