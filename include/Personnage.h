#ifndef PERSONNAGE_H
#define PERSONNAGE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    unsigned int posx;
    unsigned int posy;
} Personnage;

/* Initialise la position du personnage à celle correspondant au niveau */
void Personnage_initialiser(Personnage *perso, Niveau *niveau);
void Personnage_seDeplacer(Personnage *perso, SDLKey touche);
int Personnage_estVivant(Personnage *perso);

#endif
