#ifndef MENU_H
#define MENU_H

#include "Option.h"

typedef struct {
    Option *tableau;
    Option *courante;
} Menu;

Menu* Menu_initialiser(void);
void Menu_ajouterOption(Menu *menu, Option *option);
void Menu_supprimerOption(Menu *menu, Option *option);
void Menu_deplacerCurseur(Menu *menu); /* SDL Event */
void Menu_supprimer(Menu *menu);

#endif
