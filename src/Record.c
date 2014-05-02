#include "../include/Record.h"

Record* Record_creer(Mode* mode)
{
    Record* record=(Record*)malloc(sizeof(Record));
    /*record->fichier=;*/
    record->mode=mode;
    record->valeur=0;
    return record;
}

Record* Record_charger(FILE *fichier)
{
    unsigned int records[NB_RECORDS_MAX];
    return NULL;
}

void Record_sauvegarder(Record *record)
{

}

void Record_supprimer(Record *record)
{

}
