#include "../include/Menu.h"

SDL_Surface *surfaceMenu = NULL;
SDL_Surface *curseur = NULL;

Menu* Menu_initialiser(void)
{
	surfaceMenu = IMG_Load("img/menu.png");
	curseur = IMG_Load("img/curseur.png");
    Menu *menu = (Menu*)malloc(sizeof(Menu));

    menu->nb = 0;
    menu->tableau = (Option*)malloc(0);
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

void Menu_deplacerCurseur(Menu *menu, SDLKey touche)
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
	free(menu->tableau);
	free(menu);
}

void Menu_afficher(Menu *menu, SDL_Surface *ecran) {
	SDL_Rect position;

	position.x = 0;
	position.y = 0;

	SDL_BlitSurface(surfaceMenu, NULL, ecran, &position);
}

void Menu_derouler(Menu *menu) {
	SDL_Event event;
	int loop = 1;

	SDL_Surface *ecran = NULL;
	ecran = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);

	while (loop) {
		SDL_WaitEvent(&event);

		switch (event.type) {
			case SDL_QUIT:
				loop = 0;
				break;
			case SDL_KEYDOWN:
				Menu_deplacerCurseur(menu, event.key.keysym.sym);
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

void Menu_jouer(Menu *menu) {
	Mode *mode = NULL;
    mode = Mode_creer();
    Mode_assignerMode(mode, MONTRE);

    Profil *profil = NULL;
    profil = Profil_charger(1);
    printf("Identifiant: %d, Nom : %s\n", profil->identifiant, profil->nom);

    Partie *partie = NULL;
    partie = Partie_creer(profil, mode);

    Partie_derouler(partie);

    Partie_liberer(partie);
    Mode_liberer(mode);
    Profil_liberer(profil);
}

void Menu_afficherCurseur(Menu *menu, SDL_Surface *ecran) {
	SDL_Rect position;

	position.x = 240;
	position.y = 0;

	switch (menu->courante) {
		case 0:
			position.y = 230;
			break;
		case 1:
			position.y = 310;
			break;
		case 2:
			position.y = 390;
			break;
		default:
			break;
	}

	SDL_BlitSurface(curseur, NULL, ecran, &position);
}
