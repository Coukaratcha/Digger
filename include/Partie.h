#ifndef PARTIE_H
#define PARTIE_H

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

Partie* Partie_initialiser(void);
Partie* Partie_charger(FILE *file);
void Partie_sauvegarder(void);
void Partie_supprimer(Partie *partie);
Partie** Partie_lister(void);

#endif
