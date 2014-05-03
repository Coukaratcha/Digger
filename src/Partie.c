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

unsigned int Partie_nbPartie(void) {
    unsigned int taille = 0;

    DIR *rep = NULL;

    struct dirent *lecture = NULL;

    rep = opendir("sauvegarde");

    while ((lecture = readdir(rep))) {
        if (strcmp(lecture->d_name, ".") != 0 && strcmp(lecture->d_name, "..") != 0)
            taille++;
        /* On ne compte pas "." et "..". */
    }

    closedir(rep);

    return taille;
}

Partie** Partie_lister(void)
{
    Partie **liste = NULL;
    FILE *fichier;
    char chemin[255];
    unsigned int i = 0;

    liste = (Partie**)malloc(sizeof(Partie*)*Partie_nbPartie());

    struct dirent *lecture = NULL;

    DIR *rep;

    rep = opendir("sauvegarde");

    while ((lecture = readdir(rep))) {
        if (strcmp(lecture->d_name, ".") != 0 && strcmp(lecture->d_name, "..") != 0) {
            /* On ne compte pas "." et ".." qui apparaitront avec cette fonction */
            sprintf(chemin, "sauvegarde/%s.sauv", lecture->d_name);

            fichier = fopen(chemin, "rb");

            liste[i] = Partie_charger(fichier);

            fclose(fichier);

            i++;
        }
    }

    closedir(rep);

    return liste;
}

void Partie_libererListe(Partie **liste) {
    unsigned int nbPartie = Partie_nbPartie();
    unsigned int i;

    for (i=0; i < nbPartie; i++) {
        Partie_liberer(liste[i]);
    }

    free(liste);
}
