#ifndef PERSONNAGE_H
#define PERSONNAGE_H

typedef struct {
    unsigned int posx;
    unsigned int posy;
} Personnage;

Personnage* Personnage_initialiser(void);
void Personnage_seDeplacer(Personnage *perso); /* Introduire la notion d'évènements SDL */
int Personnage_estVivant(Personnage *perso);

#endif
