#include "../include/Personnage.h"

void Personnage_initialiser(Personnage *perso, Niveau *niveau)
{
	unsigned int i, j;
	int trouve = 0;
    perso->libre = 1;

	for (i=0; !trouve && i < HAUTEUR; i++) {
		for (j=0; !trouve && j < LARGEUR; j++) {
			if (niveau->grille[i][j] == PERSO) {
				trouve = 1;
				perso->posy = i;
				perso->posx = j;
			}
		}
	}
}

unsigned int Personnage_seDeplacer(Personnage *perso, SDLKey touche, Niveau *niveau)
{
    perso->libre =0;
	unsigned int retour = 0;
    switch(touche) {
    	case SDLK_UP: /* Si le perso n'est pas au bord sup */
    		if (perso->posy > 0) { /* S'il y a (VIDE|HERBE|FRUIT) au dessus */
    			if (niveau->grille[perso->posy - 1][perso->posx] == VIDE || niveau->grille[perso->posy - 1][perso->posx] == HERBE || niveau->grille[perso->posy - 1][perso->posx] == FRUIT) {
                    niveau->grille[perso->posy - 1][perso->posx] = PERSO;
                    niveau->grille[perso->posy][perso->posx] = VIDE;
                    perso->posy-= 1;
                    retour = 1;
                }
    		}
    		break;
    	case SDLK_DOWN: /* Si le perso n'est pas au bord inf et (il est au bord sup ou il n'y a un rocher au dessus de lui) */
    		if (perso->posy < HAUTEUR - 1 && (perso->posy == 0 || niveau->grille[perso->posy - 1][perso->posx] != ROCHER)) {
    			/* S'il y a (VIDE|HERBE|FRUIT) sous le perso */
    			if (niveau->grille[perso->posy + 1][perso->posx] == VIDE || niveau->grille[perso->posy + 1][perso->posx] == HERBE || niveau->grille[perso->posy + 1][perso->posx] == FRUIT) {
	    			niveau->grille[perso->posy + 1][perso->posx] = PERSO;
	    			niveau->grille[perso->posy][perso->posx] = VIDE;
	    			perso->posy+= 1;
	    			retour = 1;
	    		}
    		}
    		break;
    	case SDLK_RIGHT: /* Si il y un rocher à droite */
            if (perso->posx < LARGEUR - 1 && (niveau->grille[perso->posy][perso->posx + 1] == VIDE || niveau->grille[perso->posy][perso->posx + 1] == FRUIT || niveau->grille[perso->posy][perso->posx + 1] == HERBE)) {
                niveau->grille[perso->posy][perso->posx + 1] = PERSO;
                niveau->grille[perso->posy][perso->posx] = VIDE;
                perso->posx+= 1;
                retour = 1;
            } /* Sinon si il y a (VIDE|HERBE|FRUIT) à droite du perso. */
            else if (perso->posx < LARGEUR - 2 && niveau->grille[perso->posy][perso->posx + 1] == ROCHER && niveau->grille[perso->posy][perso->posx + 2] == VIDE) {
                niveau->grille[perso->posy][perso->posx + 2] = ROCHER;
                niveau->grille[perso->posy][perso->posx + 1] = PERSO;
                niveau->grille[perso->posy][perso->posx] = VIDE;
                perso->posx+= 1;
                retour = 1;
            }
    		break;
    	case SDLK_LEFT:
    		if (perso->posx > 0 && (niveau->grille[perso->posy][perso->posx - 1] == VIDE || niveau->grille[perso->posy][perso->posx - 1] == FRUIT || niveau->grille[perso->posy][perso->posx - 1] == HERBE)) {
    			niveau->grille[perso->posy][perso->posx - 1] = PERSO;
    			niveau->grille[perso->posy][perso->posx] = VIDE;
    			perso->posx-= 1;
    			retour = 1;
    		} /* Sinon si il y a (VIDE|HERBE|FRUIT) à droite du perso. */
    		else if (perso->posx > 1 && niveau->grille[perso->posy][perso->posx - 1] == ROCHER && niveau->grille[perso->posy][perso->posx - 2] == VIDE) {
    			niveau->grille[perso->posy][perso->posx - 2] = ROCHER;
    			niveau->grille[perso->posy][perso->posx - 1] = PERSO;
    			niveau->grille[perso->posy][perso->posx] = VIDE;
    			perso->posx-= 1;
    			retour = 1;
    		}
    		break;
    	default:
    		break;
    }

    return retour;
}

unsigned int Personnage_estVivant(Personnage *perso, Niveau *niveau)
{
    if (perso->posy > 0) {
        if (niveau->grille[perso->posy-1][perso->posx] == ROCHER_TOMBANT) {
            return 0;
        }
    }

    return 1;
}
