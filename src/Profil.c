#include "../include/Profil.h"

Profil* Profil_creer(void)
{
    return NULL;

}

void Profil_modifier(Profil *profil)
{
}

Profil* Profil_charger(FILE *fichier)
{
    return NULL;
}

void Profil_supprimer(Profil *profil)
{

}

unsigned int Profil_prochainID(void)
{
    unsigned int maxID = 0;
    unsigned int courrantID = maxID;

    FILE *fichier = fopen("/home/mickael/ProjetsC/Digger/profil/profil.base", "rb");

    if (fichier == NULL)
    {
        printf("Erreur [Profil_prochainId] : Ouverture de profil.base\n");
    }

    while (fread(&courrantID, sizeof(unsigned int), 1, fichier) != 0)
    {
        if (courrantID > maxID)
            maxID = courrantID;
    }

    fclose(fichier);

    return maxID+1;
}
