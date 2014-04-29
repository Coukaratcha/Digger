#ifndef ITEM_H
#define ITEM_H

#include <stdio.h>
#include <stdlib.h>

typedef enum {
    FORCE = 0, FLASHBACK = 1, KEYSWITCH = 2, ROCK = 3
} TypeItem;

typedef struct {
    unsigned int table[4];
} Item;

Item* Item_initialiser(void);
void Item_ajouter(Item *item, TypeItem type);
void Item_enlever(Item *item, TypeItem type);
void Item_faireEffet(TypeItem type);
void Item_utiliser(Item *item, TypeItem type);

#endif
