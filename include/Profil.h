#ifndef PROFIL_H
#define PROFIL_H

#define NOM_TAILLE_MAX 20

typedef struct {
    unsigned int identifiant;
    char *nom;
    FILE *fichier;
} Profil;

Profil* Profil_creer(void);
void Profil_modifier(Profil *profil);
Profil* Profil_charger(FILE *fichier);
void Profil_supprimer(Profil *profil);

#endif
