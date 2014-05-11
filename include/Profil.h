#ifndef PROFIL_H
#define PROFIL_H

#define NOM_TAILLE_MAX 20

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

typedef struct {
    unsigned int identifiant;
    char nom[NOM_TAILLE_MAX+1];
} Profil;

/* 
	Ajoute un profil dans le fichier profil/profil.base et 
	crée un profil sur la pile en renvoyant un pointeur vers ce profil 
*/
Profil* Profil_creer(void);

/*
	Modifie le nom du profil.
*/
void Profil_modifier(Profil *profil);
Profil* Profil_charger(unsigned int id);
int Profil_chercherFichier(Profil *profil);
void Profil_liberer(Profil *profil);
void Profil_detruire(Profil *profil);
unsigned int Profil_prochainID(void);
void Profil_afficherListe(SDL_Surface *ecran);
int Profil_estIndexValide(unsigned int index);

#endif
