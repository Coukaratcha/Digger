#ifndef PARTIE_H
#define PARTIE_H

#include <stdio.h>
#include <stdlib.h>

#include "../include/Item.h"
#include "../include/Niveau.h"
#include "../include/Mode.h"
#include "../include/Score.h"
#include "../include/Profil.h"

typedef struct {
    Profil *profil;
    Item *item;
    Niveau *niveau;
    Mode *mode;
    Score *score;
} Partie;

Partie* Partie_creer(Profil *profil, Mode* mode);
Partie* Partie_charger(FILE *file);
void Partie_sauvegarder(Partie *partie);
void Partie_liberer(Partie *partie);
Partie** Partie_lister(void);

#endif
