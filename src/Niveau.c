#include "../include/Niveau.h"

SDL_Surface *sprites = NULL;

Niveau* Niveau_charger(unsigned int index)
{
	char chemin[255];

	sprintf(chemin, "niveau/%d.niveau", index);

	FILE *fichier = fopen(chemin, "rb");

	sprites = IMG_Load("img/sprites.png");
	
	if(sprites==NULL)
    {
        printf("Erreur chargement sprites. \n");
        exit(34);
    }
    else printf("Sprites correctement chargés. \n");
	/*
		On initalise ici "sprites", ce code sera forcément exécuter avant d'utiliser quelconques fonctions de ce module.
		Impossible d'initialiser une variable globale avec le retour d'une fonction (non constante) lors de sa déclaration.
	*/
    Niveau *niveau = (Niveau*)malloc(sizeof(Niveau));

    niveau->index = index;

    fread(niveau->grille, sizeof(Bloc), LARGEUR*HAUTEUR, fichier);

    fclose(fichier);

    return niveau;
}

void Niveau_ordonner(Niveau *niveau)
{
	/*
		On ordonne chaque ligne, si une ligne est parfaitement ordonnée alors elle le sera toujours pour ce tour.
		De façon générale avec ce parcours, aucune modification ne peut entrainer une incohérence sur les cases précédentes.
	*/
		unsigned int i, j;

		for (i=0; i < HAUTEUR - 1; i++) {
			for (j=0; j < LARGEUR; j++) {
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
					else if (j < LARGEUR - 1 && niveau->grille[i+1][j+1]) {
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
	unsigned int i, j;

	for (i=0; i < HAUTEUR; i++) {
		for (j=0; j < LARGEUR; j++) {
			Bloc_afficher(niveau->grille[i][j], ecran, j*TAILLE_BLOC, BORD_SUP_NIVEAU + i*TAILLE_BLOC);
		}
	}
}

void Bloc_afficher(Bloc bloc, SDL_Surface *ecran, unsigned int x, unsigned int y) {

	SDL_Rect position;

	position.x = x;
	position.y = y;

	SDL_Rect section;

	section.y = 0;
	section.w = 32;
	section.h = 32;

	switch (bloc) {
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

void Niveau_liberer(Niveau *niveau) {
	free(niveau);
	SDL_FreeSurface(sprites);
}
