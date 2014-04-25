#ifndef PARTIE_H
#define PARTIE_H

#include <stdio.h>
#include <stdlib.h>

#include "Item.h"
#include "Niveau.h"
#include "Mode.h"
#include "Score.h"
#include "Profil.h"

typedef struct {
    Profil *profil;
    Item *item;
    Niveau *niveau;
    Mode *mode;
    Score *score;
    FILE *fichier;
} Partie;

Partie* Partie_creer(void);
Partie* Partie_charger(FILE *file);
void Partie_sauvegarder(Partie *partie);
void Partie_supprimer(Partie *partie);
Partie** Partie_lister(void);

#endif
