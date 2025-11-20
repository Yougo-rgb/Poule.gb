#ifndef ITEM_H
#define ITEM_H

#include <gb/gb.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_ITEMS 8
#define ITEM_WIDTH 8
#define ITEM_HEIGHT 8
#define ITEM_START_SPRITE 4

typedef enum {
    ITEM_DUMMY,
    ITEM_EGG
} ItemType;

typedef struct {
    uint8_t x;
    uint8_t y;
    ItemType type;
    uint8_t sprite_tile;
    BOOLEAN active;
    uint8_t value;
    uint8_t anime_frame;
} Item;

typedef struct {
    Item items[MAX_ITEMS];
    uint8_t count;
} ItemManager;

void item_manager_init(ItemManager* manager);
void item_spawn(ItemManager* manager, uint8_t x, uint8_t y, ItemType type, uint8_t value);
void item_update(ItemManager* manager);
void item_render(ItemManager* manager);
void item_check_collision(ItemManager* manager, uint8_t px, uint8_t py, uint8_t pw, uint8_t ph, void (*on_collect)(ItemType, uint8_t, uint8_t));
void item_remove(ItemManager* manager, uint8_t index);

#endif