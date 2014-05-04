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
void Item_faireEffet(TypeItem type);
void Item_utiliser(Item *item, TypeItem type);
void Item_liberer(Item *item);
SDL_Rect Item_force(SDL_Rect positionPerso, Niveau* niveau);
Niveau* Item_flashback(Niveau* niveau);
Personnage* Item_keyswitch(Personnage *perso, Niveau *niveau);
Niveau* Item_rock(Niveau* niveau);

#endif
