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
    FILE *fichier;
} Partie;

Partie* Partie_creer(void);
Partie* Partie_charger(FILE *file);
void Partie_sauvegarder(Partie *partie);
void Partie_supprimer(Partie *partie);
Partie** Partie_lister(void);

#endif
