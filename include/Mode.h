#ifndef MODE_H
#define MODE_H

#include <stdio.h>
#include <stdlib.h>

typedef enum {
    NORMAL,
    MONTRE,
    BONUS,
    DEFAULT
} TypeMode;

typedef struct {
    TypeMode type;
} Mode;

Mode* Mode_creer(void);
void Mode_assignerMode(Mode* mode, TypeMode type);
void Mode_chargerRegles(Mode *mode);

#endif
