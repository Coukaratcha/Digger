#include "../include/Partie.h"

Partie* Partie_creer(void)
{
    Partie* partie= (Partie*)malloc(sizeof(Partie));
    partie->profil= Profil_creer();
    partie->item= Item_initialiser();
    partie->score= Score_initialiser();
    partie->mode= Mode_creer();
    /*partie->fichier=;*/
    return partie;
}

Partie* Partie_charger(FILE *file)
{
    return NULL;
}

void Partie_sauvegarder(Partie *partie)
{

}

void Partie_supprimer(Partie *partie)
{

}

Partie** Partie_lister(void)
{
    return NULL;
}
