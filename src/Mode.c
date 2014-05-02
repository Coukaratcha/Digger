#include "../include/Mode.h"

Mode* Mode_creer(void)
{
    Mode* mode=(Mode*)malloc(sizeof(Mode));
    mode->type=DEFAULT;
    return mode;
}

Mode* Mode_assignerMode(Mode* mode, unsigned int numeroMode)
{
    if(mode->type==DEFAULT)
    {
        switch(numeroMode)
        {
        case 0:
            mode->type=NORMAL;
            break;

        case 1:
            mode->type=MONTRE;
            break;

        case 2:
            mode->type=BONUS;
            break;

        default:
            break;
        }
        return mode;
    }
    else{
        return NULL;
    }
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
