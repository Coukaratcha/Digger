#ifndef MODE_H
#define MODE_H

#include <stdio.h>
#include <stdlib.h>

typedef enum {
    NORMAL,
    MONTRE,
    BONUS
} TypeMode;

typedef struct {
    TypeMode type;
} Mode;

Mode* Mode_creer(void);
void Mode_chargerRegles(Mode *mode);

#endif
