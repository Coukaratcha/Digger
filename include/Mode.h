#ifndef MODE_H
#define MODE_H

#include "Partie.h"

typedef enum {
    NORMAL,
    MONTRE,
    BONUS
} TypeMode;

typedef struct {
    TypeMode mode;
} Mode;

Mode* Mode_creer(void);

#endif
