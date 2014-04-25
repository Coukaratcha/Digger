#ifndef SCORE_H
#define SCORE_H

#include <stdio.h>
#include <stdlib.h>

#include "Partie.h"
#include "Mode.h"

typedef struct {
    unsigned int temps;
    unsigned int pas;
    Mode *mode;
} Score;

Score* Score_creer(void);
void Score_augmenter(Score *score, unsigned int points);
void Score_miseAJour(Score *score);

#endif
