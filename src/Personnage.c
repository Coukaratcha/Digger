#include "../include/Personnage.h"

void Personnage_initialiser(Personnage *perso, Niveau *niveau)
{
	unsigned int i, j;
	int trouve = 0;

	for (i=0; !trouve; i++) {
		for (j=0; !trouve; j++) {
			if (niveau->grille[i][j] == PERSO) {
				trouve = 1;
				perso->posx = i*32;
				perso->posy = BORD_SUP_NIVEAU+j*32;
			}
		}
	}
}

unsigned int Personnage_seDeplacer(Personnage *perso, SDL_Event *event)
{
    
}

unsigned int Personnage_estVivant(Personnage *perso)
{
    return 0;
}
