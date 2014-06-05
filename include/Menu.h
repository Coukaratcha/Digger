#ifndef MENU_H
#define MENU_H

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "Partie.h"

#define OPTION_TAILLE_MAX 20

typedef enum {
	JOUER,
	OPTIONS,
	QUITTER
} Option;

typedef struct {
    Option *tableau;
    unsigned int courante;
    unsigned int nb;
    int libre;
} Menu;

Menu* Menu_initialiser(void);
void Menu_ajouterOption(Menu *menu, Option option);
void Menu_supprimerOption(Menu *menu, unsigned int index);
void Menu_deplacerCurseur(Menu *menu, SDLKey touche, SDL_Surface *ecran); /* SDL Event */
void Menu_liberer(Menu *menu);
void Menu_afficher(Menu *menu, SDL_Surface *ecran);
void Menu_lancer(Menu *menu, SDL_Surface *ecran, Profil *profil);
void Menu_jouer(SDL_Surface *ecran, Profil *profil);
void Menu_derouler(Menu *menu, SDL_Surface *ecran, Profil *profil);
void Menu_afficherCurseur(Menu *menu, SDL_Surface *ecran);
void Menu_interagir(Menu *menu, SDLKey touche, SDL_Surface *ecran, Profil *profil);

#endif
