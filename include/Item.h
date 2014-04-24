#ifndef ITEM_H
#define ITEM_H

typedef enum {
    FORCE = 0, FLASHBACK = 1, KEYSWITCH = 2, ROCK = 3
} Type;

typedef struct {
    unsigned int table[4];
} Item;

Item* Item_initialiser(void);
void Item_ajouter(Type item);
void Item_enlever(Type item);
void Item_faireEffet(Type item);

#endif
