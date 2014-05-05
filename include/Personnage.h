#ifndef PERSONNAGE_H
#define PERSONNAGE_H

#include <stdio.h>
#include <stdlib.h>

#include "../include/Niveau.h"

typedef struct {
    unsigned int posx;
    unsigned int posy;
} Personnage;

/* Initialise la position du personnage à celle correspondant au niveau */
void Personnage_initialiser(Personnage *perso, Niveau *niveau);
unsigned int Personnage_seDeplacer(Personnage *perso, SDL_Event *event); /* Renvoie 1 si le personnage peut se déplacer, 0 sinon.*/
unsigned int Personnage_estVivant(Personnage *perso);

#endif
