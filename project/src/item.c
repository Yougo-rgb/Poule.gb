#include "item.h"
#include "audio.h"

#define SPRITE_EGG 4

void item_manager_init(ItemManager* manager) {
    manager->count = 0;
    for (uint8_t i = 0; i < MAX_ITEMS; i++) {
        manager->items[i].active = FALSE;
        manager->items[i].type = ITEM_DUMMY;
    }
}

void item_spawn(ItemManager* manager, uint8_t x, uint8_t y, ItemType type, uint8_t value) {

    for(uint8_t i = 0; i < MAX_ITEMS; i++) {
        if (!manager->items[i].active) {
            manager->items[i].x = x;
            manager->items[i].y = y;
            manager->items[i].type = type;
            manager->items[i].value = value;
            manager->items[i].active = TRUE;
            // manager->items[i].anime_frame = 0; 
            
            switch(type) {
                case ITEM_EGG:
                    manager->items[i].sprite_tile = SPRITE_EGG + (x % 4);
                    break;

                default:
                    manager->items[i].sprite_tile = SPRITE_EGG;
            }

            manager->count++;
            return;
        }
    }
}

void item_update(ItemManager* manager) {
    for(uint8_t i = 0; i < MAX_ITEMS; i++) {
        if (manager->items[i].active) {
            // manager->items[i].anime_frame++;
        }
    }
}

void item_render(ItemManager* manager) {
    for(uint8_t i = 0; i < MAX_ITEMS; i++) {
        if (manager->items[i].active) {
            uint8_t sprite_index = ITEM_START_SPRITE + i;

            move_sprite(sprite_index, manager->items[i].x, manager->items[i].y);
            set_sprite_tile(sprite_index, manager->items[i].sprite_tile);
        } else {
            hide_sprite(ITEM_START_SPRITE + i);
        }
    }
}

void item_check_collision(ItemManager* manager, uint8_t px, uint8_t py, uint8_t pw, uint8_t ph, void (*on_collect)(ItemType, uint8_t, uint8_t)) {
    for (uint8_t i = 0; i < MAX_ITEMS; i++) {

        if (!manager->items[i].active) continue;

        BOOLEAN collision = !(
            px + pw < manager->items[i].x ||
            px > manager->items[i].x + ITEM_WIDTH||
            py + ph < manager->items[i].y ||
            py > manager->items[i].y + ITEM_HEIGHT
        );

        if (collision) {
            if(on_collect != NULL) {
                on_collect(
                    manager->items[i].type, 
                    manager->items[i].value, 
                    i
                );
            }
        }
    }
}

void item_remove(ItemManager* manager, uint8_t index) {
    if (index < MAX_ITEMS && manager->items[index].active) {
        manager->items[index].active = FALSE;
        hide_sprite(ITEM_START_SPRITE + index);
        manager->count--;
    }
}