#ifndef MODE_H
#define MODE_H

#include "Partie.h"

typedef enum {
    NORMAL,
    MONTRE,
    BONUS
} TypeMode;

typedef struct {
    TypeMode type;
} Mode;

Mode* Mode_creer(void);
void Mode_supprimer(Mode *mode);

#endif
