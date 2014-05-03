#include "../include/Item.h"

Item* Item_initialiser(void)
{
   Item* item=(Item*)malloc(sizeof(Item));
   item->table[FORCE]=0;
   item->table[FLASHBACK]=0;
   item->table[KEYSWITCH]=0;
   item->table[ROCK]=0;
   return item;
}

void Item_ajouter(Item *item, TypeItem type)
{
    switch(type)
    {
    case FORCE:
        item->table[FORCE]++;
        break;
    case FLASHBACK:
        item->table[FLASHBACK]++;
        break;
    case KEYSWITCH:
        item->table[KEYSWITCH]++;
        break;
    case ROCK:
        item->table[ROCK]++;
        break;
    default:
        break;
    }
}

unsigned int Item_enlever(Item *item, TypeItem type)
{
    switch(type)
    {
    case FORCE:
        if(item->table[FORCE]!=0)
        {
            item->table[FORCE]--;
            return 0; //on renvoie 0 pour dire que tout s'est bien passé et qu'on peut enlever un item
        }
        else return 1; // on renvoie 1 si il y a une erreur, c-à-d si on ne peut pas utiliser un item car on n'en a pas assez
        break;

    case FLASHBACK:
        if(item->table[FLASHBACK]!=0)
        {
            item->table[FLASHBACK]--;
            return 0;
        }
        else return 1;
        break;

    case KEYSWITCH:
        if(item->table[KEYSWITCH]!=0)
        {
            item->table[KEYSWITCH]--;
            return 0;
        }
        else return 1;
        break;

    case ROCK:
        if(item->table[ROCK]!=0)
        {
            item->table[ROCK]--;
            return 0;
        }
        else return 1;
        break;

    default:
        return 1;
        break;
    }
}

void Item_force()
{

}

void Item_flashback()
{

}

SDL_Rect Item_keyswitch(SDL_Rect positionPerso, Niveau* niveau)
{
    SDL_Event event;
    unsigned int nb_tours=0;

    while(nb_tours<10)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_UP: // Flèche haut = gauche
                        positionPerso.x-=32;
                        nb_tours++;
                        Niveau_ordonner(niveau);
                        break;

                    case SDLK_DOWN: // Flèche bas = haut
                        positionPerso.y-=32;
                        nb_tours++;
                        Niveau_ordonner(niveau);
                        break;

                    case SDLK_RIGHT: // Flèche droite = bas
                        positionPerso.y+=32;
                        nb_tours++;
                        Niveau_ordonner(niveau);
                        break;

                    case SDLK_LEFT: // Flèche gauche = droite
                        positionPerso.x+=32;
                        nb_tours++;
                        Niveau_ordonner(niveau);
                        break;

                    default:
                        break;
                }
             default:
                break;
        }
    }
    return positionPerso;
}

void Item_rock()
{

}

