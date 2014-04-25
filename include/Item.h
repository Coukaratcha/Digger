#ifndef ITEM_H
#define ITEM_H

#include "Partie.h"

typedef enum {
    FORCE = 0, FLASHBACK = 1, KEYSWITCH = 2, ROCK = 3
} TypeItem;

typedef struct {
    unsigned int table[4];
} Item;

Item* Item_initialiser(void);
void Item_ajouter(TypeItem item);
void Item_enlever(TypeItem item);
void Item_faireEffet(TypeItem item);

#endif
