#ifndef NIVEAU_H
#define NIVEAU_H

#include "Partie.h"

typedef enum {
    VIDE,
    HERBE,
    MUR,
    FRUIT,
    ROCHER,
    PERSO
} Bloc;

typedef struct {
    unsigned int largeur;
    unsigned int hauteur;
    Bloc **grille;
    FILE *fichier;
} Niveau;

Niveau* Niveau_charger(FILE *fichier);
<<<<<<< HEAD
void Niveau_afficher(void);
=======
void Niveau_ordonner(Niveau *niveau);
void Niveau_afficer(Niveau *niveau);
>>>>>>> 24240dc8d906d28172308b400a9c5e12fe215fe8

#endif
