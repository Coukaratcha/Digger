#ifndef PROFIL_H
#define PROFIL_H

#define NOM_TAILLE_MAX 20

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

typedef struct {
    unsigned int identifiant;
    char nom[NOM_TAILLE_MAX];
} Profil;

Profil* Profil_creer(void);
void Profil_modifier(Profil *profil);
Profil* Profil_charger(FILE *fichier, unsigned int id);
void Profil_supprimer(Profil *profil);
unsigned int Profil_prochainID(void);

#endif
