#ifndef NIVEAU_H
#define NIVEAU_H

#include <stdio.h>
#include <stdlib.h>

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
    unsigned int largeur;
    unsigned int hauteur;
    Bloc **grille;
    FILE *fichier;
} Niveau;

Niveau* Niveau_charger(FILE *fichier);
void Niveau_ordonner(Niveau *niveau);
void Niveau_afficher(Niveau *niveau);

#endif
