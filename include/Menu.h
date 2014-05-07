#ifndef MENU_H
#define MENU_H

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#define OPTION_TAILLE_MAX 20

typedef struct {
    char **tableau;
    unsigned int courante;
    unsigned int nb;
} Menu;

Menu* Menu_initialiser(void);
void Menu_ajouterOption(Menu *menu, char *nom);
void Menu_supprimerOption(Menu *menu, unsigned int index);
void Menu_deplacerCurseur(Menu *menu, SDLKey touche); /* SDL Event */
void Menu_supprimer(Menu *menu);
void Menu_afficher(Menu *menu, SDL_Surface *ecran);

#endif
