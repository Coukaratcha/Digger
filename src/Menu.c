#include "../include/Menu.h"

SDL_Surface *surfaceMenu = NULL;
SDL_Surface *curseur = NULL;
int loop = 1;

Menu* Menu_initialiser(void)
{
	surfaceMenu = IMG_Load("img/menu.png");
	curseur = IMG_Load("img/curseur.png");
    Menu *menu = (Menu*)malloc(sizeof(Menu));

    menu->tableau = NULL;

    menu->nb = 0;
    menu->courante = 0;
    menu->libre = 1;

    return menu;
}

void Menu_ajouterOption(Menu *menu, Option option)
{
	menu->nb++;
	menu->tableau = (Option*)realloc(menu->tableau, sizeof(Option)*menu->nb);

	menu->tableau[menu->nb - 1] = option;
}

void Menu_supprimerOption(Menu *menu, unsigned int index)
{
	if (index < menu->nb) {
		unsigned int i;

		for (i=index; i < menu->nb - 1; i++) {
			menu->tableau[i] = menu->tableau[i+1];
		}

		menu->nb--;
		menu->tableau = (Option*)realloc(menu->tableau, sizeof(Option)*menu->nb);
	}
}

void Menu_deplacerCurseur(Menu *menu, SDLKey touche, SDL_Surface *ecran)
{
	if (menu->libre) {
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
}

void Menu_liberer(Menu *menu)
{
    SDL_FreeSurface(curseur);
    SDL_FreeSurface(surfaceMenu);
	free(menu->tableau);
	free(menu);
}

void Menu_afficher(Menu *menu, SDL_Surface *ecran) {
	SDL_Rect position;

	position.x = 0;
	position.y = 0;

	SDL_BlitSurface(surfaceMenu, NULL, ecran, &position);
}

void Menu_derouler(Menu *menu, SDL_Surface *ecran) {
	SDL_Event event;

	while (loop) {
		SDL_WaitEvent(&event);

		switch (event.type) {
			case SDL_QUIT:
				loop = 0;
				break;
			case SDL_KEYDOWN:
				Menu_interagir(menu, event.key.keysym.sym, ecran);
				menu->libre = 0;
				break;
			case SDL_KEYUP:
				menu->libre = 1;
			default:
				break;
		}

		SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
		Menu_afficher(menu, ecran);
		Menu_afficherCurseur(menu, ecran);
		SDL_Flip(ecran);
	}
}

void Menu_jouer(SDL_Surface *ecran) {
	Mode *mode = NULL;
    mode = Mode_creer();
    Mode_assignerMode(mode, MONTRE);

    Profil *profil = NULL;
    profil = Profil_charger(1);
    printf("Identifiant: %d, Nom : %s\n", profil->identifiant, profil->nom);

    Partie *partie = NULL;
    partie = Partie_creer(profil, mode);

    Partie_derouler(partie, ecran);

    Partie_liberer(partie);
    Mode_liberer(mode);
    Profil_liberer(profil);
}

void Menu_afficherCurseur(Menu *menu, SDL_Surface *ecran) {
	SDL_Rect position;

	position.x = 240;
	position.y = 0;

	switch (menu->tableau[menu->courante]) {
		case JOUER:
			position.y = 230;
			break;
		case OPTIONS:
			position.y = 310;
			break;
		case QUITTER:
			position.y = 390;
			break;
		default:
			break;
	}

	SDL_BlitSurface(curseur, NULL, ecran, &position);
}

void Menu_lancer(Menu *menu, SDL_Surface *ecran) {
	switch (menu->tableau[menu->courante]) {
		case JOUER:
			Menu_jouer(ecran);
			break;
		case QUITTER:
			loop = 0;
		default:
			break;
	}
}

void Menu_interagir(Menu *menu, SDLKey touche, SDL_Surface *ecran) {
	if (touche == SDLK_RETURN) {
		Menu_lancer(menu, ecran);
	}
	else if (touche == SDLK_UP ||touche == SDLK_DOWN) {
		Menu_deplacerCurseur(menu, touche, ecran);
	}
}
