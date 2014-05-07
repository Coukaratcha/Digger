#include "../include/Menu.h"

SDL_Surface * surfaceMenu = NULL;

Menu* Menu_initialiser(void)
{
	surfaceMenu = IMG_Load("img/menu.png");
    Menu *menu = (Menu*)malloc(sizeof(Menu));

    menu->nb = 0;
    menu->tableau = (char**)malloc(sizeof(char[OPTION_TAILLE_MAX])*0);
    menu->courante = 0;

    return menu;
}

void Menu_ajouterOption(Menu *menu, char *nom)
{
	unsigned int i;

	menu->nb++;
	menu->tableau = (char**)realloc(menu->tableau, sizeof(char[OPTION_TAILLE_MAX])*menu->nb);

	for (i = 0; i < OPTION_TAILLE_MAX; i++) {
		menu->tableau[menu->nb - 1][i] = nom[i];
	}
}

void Menu_supprimerOption(Menu *menu, unsigned int index)
{
	if (index < menu->nb) {
		unsigned int i, j;

		for (i=index; i < menu->nb - 1; i++) {
			for (j=0; j < OPTION_TAILLE_MAX; j++) {
				menu->tableau[i][j] = menu->tableau[i+1][j];
			}
		}

		free(menu->tableau+menu->nb);
		menu->nb--;
		menu->tableau = (char**)realloc(menu->tableau, sizeof(char[OPTION_TAILLE_MAX])*menu->nb);
	}
}

void Menu_deplacerCurseur(Menu *menu, SDLKey touche)
{
	switch(touche) {
		case SDLK_UP:
			if (menu->courante > 0)
				menu->courante--;
			break;
		case SDLK_DOWN:
			if (menu->courante < menu->nb - 1)
				menu->courante++;
			break;
		default:
		break;
	}
}

void Menu_liberer(Menu *menu)
{
	unsigned int i;

	for (i=0; i < menu->nb; i++) {
		free(menu->tableau[i]);
	}

	free(menu->tableau);
	free(menu);
}

void Menu_afficher(Menu *menu, SDL_Surface *ecran) {
	SDL_Rect position;

	position.x = 0;
	position.y = 0;

	SDL_BlitSurface(surfaceMenu, NULL, ecran, &position);
}
