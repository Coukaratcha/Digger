#ifndef GERER_ENTREES_H
#define GERER_ENTREES_H

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL_ttf.h>

#define TEXTE_TAILLE_MAX 20

typedef enum {
	NUM, 
	TEXTE
} TypeEntree;

typedef struct {
	TypeEntree type;
	char texte[TEXTE_TAILLE_MAX+1];
	char current;
	unsigned int num;
	SDL_Surface *surfaceCurrent;
	SDL_Surface *surfaceTexte;
} Entree;

Entree* Entree_creer(TypeEntree type);
void Entree_liberer(Entree *entree);

void GererEntrees_initialiser(void);
void GererEntrees_derouler(SDL_Surface *ecran, Entree *entree, SDL_Event *event);
void GererEntrees_interface(SDLKey touche, Entree *entree);
void GererEntrees_changerNum(SDLKey touche, Entree *entree);
void GererEntrees_changerCar(SDLKey touche, Entree *entree);
void GererEntrees_afficherEntree(Entree *entree, SDL_Surface *ecran);
void GererEntrees_afficherNum(Entree *entree, SDL_Surface *ecran);
void GererEntrees_afficherCar(Entree *entree, SDL_Surface *ecran);
void GererEntrees_afficherText(Entree *entree, SDL_Surface *ecran);
void GererEntrees_ajouterCar(Entree *entree);
void GererEntrees_supprimerCar(Entree *entree);
void GererEntrees_liberer(void);

#endif