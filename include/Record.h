#ifndef RECORD_H
#define RECORD_H

#include "Mode.h"

typedef struct {
    FILE *fichier;
    Mode *mode;
    unsigned int valeur;
} Record;

Record* Record_creer(void);
Record* Record_charger(FILE *fichier);
void Record_sauvegarder(Record *record);
void Record_supprimer(Record *record);

#endif
