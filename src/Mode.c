#include "../include/Mode.h"

Mode* Mode_creer(void)
{
    Mode* mode=(Mode*)malloc(sizeof(Mode));
    mode->type=DEFAULT;
    return mode;
}

void Mode_assignerMode(Mode* mode, TypeMode type)
{
    mode->type = type;
}

void Mode_chargerRegles(Mode *mode)
{
    switch(mode->type)
    {
    case NORMAL:
        break;

    case MONTRE:
        break;

    case BONUS:
        break;

    default:
        break;
    }
}
