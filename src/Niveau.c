#include "../include/Niveau.h"

SDL_Surface *sprites = NULL;

Niveau* Niveau_charger(FILE *fichier)
{
	sprites = IMG_Load("../../img/sprites.png"); 
	/* 
		On initalise ici "sprites", ce code sera forcément exécuter avant d'utiliser quelconques fonctions de ce module.
		Impossible d'initialiser une variable globale avec le retour d'une fonction (non constante) lors de sa déclaration.
	*/
    Niveau *niveau = (Niveau*)malloc(sizeof(Niveau));
    unsigned int i;

    fread(&(niveau->largeur), sizeof(unsigned int), 1, fichier);
    fread(&(niveau->hauteur), sizeof(unsigned int), 1, fichier);

    for (i=0; i < niveau->hauteur; i++) {
    	fread(niveau->grille[i], sizeof(Bloc), niveau->largeur, fichier);
    }

    return niveau;
}

void Niveau_ordonner(Niveau *niveau)
{
	/* 
		On ordonne chaque ligne, si une ligne est parfaitement ordonnée alors elle le sera toujours pour ce tour.
		De façon générale avec ce parcours, aucune modification ne peut entrainer une incohérence sur les cases précédentes.
	*/
		unsigned int i, j;

		for (i=0; i < niveau->hauteur - 1; i++) {
			for (j=0; j < niveau->largeur; j++) {
				if (niveau->grille[i][j] == ROCHER && niveau->grille[i+1][j] == VIDE)
					niveau->grille[i][j] = ROCHER_TOMBANT;
				/*
					Si le rocher n'est plus maintenu directement en dessous lui, il devient tombant.
				*/
				if (niveau->grille[i][j] == ROCHER_TOMBANT) {
					if (niveau->grille[i+1][j] == VIDE){
						niveau->grille[i][j] = VIDE;
						niveau->grille[i+1][j] = ROCHER_TOMBANT;
					}
					/*
						Un rocher tombant cherchera à aller en dessous directement en priorité.
					*/
					else if (j > 0 && niveau->grille[i+1][j-1]) {
						niveau->grille[i][j] = VIDE;
						niveau->grille[i+1][j-1] = ROCHER_TOMBANT;
					}
					/* 
						S'il ne peut pas, il cherchera à aller en bas à gauche.
					*/
					else if (j < niveau->largeur - 1 && niveau->grille[i+1][j+1]) {
						niveau->grille[i][j] = VIDE;
						niveau->grille[i+1][j+1] = ROCHER_TOMBANT;
					}
					/*
						S'il ne peut pas non plus, il cherchera à aller en bas à droite.
					*/
					else {
						niveau->grille[i][j] = ROCHER;
					}
					/*
						Sinon, il redevient alors un rocher normal, et on continue de ranger le reste du niveau.
					*/
				}
			}
		}
}

void Niveau_afficher(Niveau *niveau, SDL_Surface *ecran)
{

}

void Bloc_afficher(Bloc *bloc, SDL_Surface *ecran, unsigned int x, unsigned int y) {
	
	SDL_Rect position;

	position.x = x;
	position.y = y;

	SDL_Rect section;

	section.y = 0;
	section.w = 32;
	section.h = 32;

	switch (*bloc) {
		case VIDE:
			section.x = 32*5;
			break;
		case HERBE:
			section.x = 32*3;
			break;
		case MUR:
			section.x = 0;
			break;
		case FRUIT:
			section.x = 32*2;
			break;
		case ROCHER:
			section.x = 32*4;
			break;
		case ROCHER_TOMBANT:
			section.x = 32*4;
			break;
		case PERSO:
			section.x = 32;
			break;
		default:
			section.x = 0; /* Si c'est ça, y'a un problème */
			break;
	}

	SDL_BlitSurface(sprites, &section, ecran, &position);
}