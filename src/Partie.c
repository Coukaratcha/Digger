#include "../include/Partie.h"

Partie* Partie_creer(Profil *profil, Mode* mode)
{
    Partie* partie= (Partie*)malloc(sizeof(Partie));

    partie->profil= profil;
    partie->item= Item_initialiser();
    partie->mode= mode;
    partie->score= Score_initialiser(mode);
    partie->niveau= Niveau_charger(1);
    return partie;
}

Partie* Partie_charger(FILE *fichier)
{
    Partie *partie = (Partie*)malloc(sizeof(Partie));

    unsigned int indexProfil, indexNiveau;

    fread(&indexProfil, sizeof(unsigned int), 1, fichier);

    partie->profil = Profil_charger(indexProfil);
    fread(partie->item, sizeof(Item), 1, fichier);
    fread(partie->mode, sizeof(Mode), 1, fichier);
    fread(partie->score, sizeof(Score), 1, fichier);

    fread(&indexNiveau, sizeof(unsigned int), 1, fichier);

    partie->niveau = Niveau_charger(indexNiveau);

    fclose(fichier);

    return partie;
}

void Partie_sauvegarder(Partie *partie)
{
    char chemin[255];

    sprintf(chemin, "sauvegarde/%d-%d.sauv", partie->profil->identifiant, partie->niveau->index);

    FILE *fichier = fopen(chemin, "wb");

    fwrite(&(partie->profil->identifiant), sizeof(unsigned int), 1, fichier);
    fwrite(partie->item, sizeof(Item), 1, fichier);
    fwrite(partie->mode, sizeof(Mode), 1, fichier);
    fwrite(partie->score, sizeof(Score), 1, fichier);
    fwrite(&(partie->profil->identifiant), sizeof(unsigned int), 1, fichier);

    fclose(fichier);
}

void Partie_liberer(Partie *partie)
{
    Score_liberer(partie->score);
    Niveau_liberer(partie->niveau);
    Item_liberer(partie->item);
}

void Partie_detruireSauv(Partie *partie) {
    char chemin[255];

    sprintf(chemin, "sauvegarde/%d-%d.sauv", partie->profil->identifiant, partie->niveau->index);

    remove(chemin);
}

Partie** Partie_lister(void)
{
    return NULL;
}
