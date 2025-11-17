#include <gb/gb.h>
#include <stdio.h>
#include "./assets/Background.c"
#include "./assets/BackgroundTile.c"
//#include "./assets/Character.c"
#include "./assets/ChickenLittle.c"
#include "./assets/EggLittle.c"

void main(){
    UINT8 currentspriteindex = 0;
    set_bkg_data(0, 11, backTile);
    set_bkg_submap(0, 0, 20, 18, backMap, 20);

    set_sprite_data(0, 4, chickenLittleSprite);
    set_sprite_tile(0, currentspriteindex);

    move_sprite(0, 88, 80);
    SHOW_BKG;
    DISPLAY_ON;
    SHOW_SPRITES;

    while(1){
        switch(joypad()){
            case J_LEFT:
                currentspriteindex = 1;
                scroll_sprite(0, -8, 0);
                break;
            case J_RIGHT:
                currentspriteindex = 0;
                scroll_sprite(0, 8, 0);
                break;
            case J_UP:
                currentspriteindex = 0;
                scroll_sprite(0, 0, -8);
                break;
            case J_DOWN:
                currentspriteindex = 3;
                scroll_sprite(0, 0, 8);
                break;
            case J_A:
                printf("A");
                break;
            case J_B:
                printf("B");
                break;
        };
        set_sprite_tile(0, currentspriteindex);
        delay(100);
    }

}