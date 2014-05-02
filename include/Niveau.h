#ifndef NIVEAU_H
#define NIVEAU_H

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#define BORD_SUP_NIVEAU 24
#define HAUTEUR 18
#define LARGEUR 25
#define TAILLE_BLOC 32

typedef enum {
    VIDE,
    HERBE,
    MUR,
    FRUIT,
    ROCHER,
    ROCHER_TOMBANT,
    PERSO
} Bloc;

typedef struct {
    Bloc grille[18][25];
    FILE *fichier;
} Niveau;

Niveau* Niveau_charger(FILE *fichier);
void Niveau_ordonner(Niveau *niveau);
void Niveau_afficher(Niveau *niveau, SDL_Surface *ecran);
void Bloc_afficher(Bloc bloc, SDL_Surface *ecran, unsigned int x, unsigned int y);

#endif
