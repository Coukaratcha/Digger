#ifndef PARTIE_H
#define PARTIE_H

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

#ifndef WIN32
	#include <sys/types.h>
#endif

#include "../include/Item.h"
#include "../include/Niveau.h"
#include "../include/Mode.h"
#include "../include/Score.h"
#include "../include/Profil.h"

typedef struct {
    Profil *profil;
    Item *item;
    Niveau *niveau;
    Mode *mode;
    Score *score;
} Partie;

Partie* Partie_creer(Profil *profil, Mode* mode);
Partie* Partie_charger(FILE *file);
void Partie_sauvegarder(Partie *partie);
void Partie_liberer(Partie *partie);
void Partie_detruireSauv(Partie *partie);

int Partie_estFinie(Partie *partie);
unsigned int Partie_nbFruitRestants(Partie *partie);

unsigned int Partie_nbPartie(void);
Partie** Partie_lister(void);
void Parti_libererListe(Partie **liste);

#endif
