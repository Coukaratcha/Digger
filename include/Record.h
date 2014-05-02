#ifndef RECORD_H
#define RECORD_H

#include <stdio.h>
#include <stdlib.h>

#include "../include/Mode.h"

#define NB_RECORDS_MAX 10

typedef struct {
    FILE *fichier;
    Mode *mode;
    unsigned int valeur;
} Record;

Record* Record_creer(Mode* mode);
Record* Record_charger(FILE *fichier);
void Record_sauvegarder(Record *record);
void Record_supprimer(Record *record);

#endif
