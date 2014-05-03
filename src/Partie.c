#include "../include/Partie.h"

Partie* Partie_creer(Mode* mode)
{
    Partie* partie= (Partie*)malloc(sizeof(Partie));
    partie->profil= Profil_creer();
    partie->item= Item_initialiser();
<<<<<<< HEAD
    partie->score= Score_initialiser(mode);
    partie->mode= mode;
=======
    partie->mode= Mode_creer();
    partie->score= Score_initialiser(partie->mode);
>>>>>>> 09b7419f8f3619d91ea87d6e96643ce77c6d9390
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
