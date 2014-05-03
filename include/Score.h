#ifndef SCORE_H
#define SCORE_H

#include <stdio.h>
#include <stdlib.h>

#include "Mode.h"
#include <SDL/SDL_ttf.h>

typedef struct {
    unsigned int temps;
    unsigned int pas;
    Mode mode;
    SDL_Surface *texte;
} Score;

Score* Score_initialiser(Mode *mode);
void Score_augmenter(Score *score, int points);
void Score_miseAJour(Score *score);
void Score_afficher(Score *score, SDL_Surface *ecran);
void Score_liberer(Score *score);

#endif
