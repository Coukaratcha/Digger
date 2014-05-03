#ifndef ITEM_H
#define ITEM_H

#include <stdio.h>
#include <stdlib.h>
#include "../include/Niveau.h"
#include "../include/Personnage.h"

typedef enum {
    FORCE = 0, FLASHBACK = 1, KEYSWITCH = 2, ROCK = 3
} TypeItem;

typedef struct {
    unsigned int table[4];
} Item;

Item* Item_initialiser(void);
void Item_ajouter(Item *item, TypeItem type);
unsigned int Item_enlever(Item *item, TypeItem type);
void Item_force();
void Item_flashback();
SDL_Rect Item_keyswitch(SDL_Rect positionPerso, Niveau *niveau);
void Item_rock();

#endif
