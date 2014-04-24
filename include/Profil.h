#ifndef PROFIL_H
#define PROFIL_H

typedef struct {
    unsigned int identifiant;
    char *nom;
    FILE *fichier;
} Profil;

Profil* Profil_creer(void);
void Profil_modifier(Profil *profil);
void Profil_charger(FILE *fichier);
void Profil_supprimer(Profil *profil);

#endif
