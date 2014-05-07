#include "../include/Item.h"

#include <time.h> // pour utiliser srand()

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
            return 0; //on renvoie 0 pour dire que tout s'est bien pass� et qu'on peut enlever un item
        }
        else return 1; // on renvoie 1 si il y a une erreur, c-�-d si on ne peut pas utiliser un item car on n'en a pas assez
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

void Item_force(Personnage* perso, Niveau* niveau)
{

}

void Item_flashback(Niveau* niveau, Bloc** grilleSauv)
{
    /* grilleSauv contient l'�tat du niveau avant le dernier coup du joueur */
    unsigned int i;
    unsigned int j;

    for(i=0;i<18;i++)
    {
        for(j=0;j<25;j++)
        {
            /* On parcours toutes les case de grilleSauv et on le remet dans niveau de telles sortes que l'on r�tablisse
            l'�tat du niveau avant le dernier coup du joueur */
            niveau->grille[i][j]=grilleSauv[i][j];
        }
    }
}

void Item_keyswitch(Personnage *perso, Niveau* niveau)
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
                    case SDLK_UP: /* Fl�che haut = gauche */
                        if(Personnage_seDeplacer(perso,SDLK_LEFT,niveau)) /* Si le d�placement est possible */
                        {
                            nb_tours++;
                            Niveau_ordonner(niveau);
                        }
                        break;

                    case SDLK_DOWN: /* Fl�che bas = haut */
                        if(Personnage_seDeplacer(perso,SDLK_UP,niveau))
                        {
                            nb_tours++;
                            Niveau_ordonner(niveau);
                        }
                        break;

                    case SDLK_RIGHT: /* Fl�che droite = bas */
                        if(Personnage_seDeplacer(perso,SDLK_DOWN,niveau))
                        {
                            nb_tours++;
                            Niveau_ordonner(niveau);
                        }
                        break;

                    case SDLK_LEFT: /* Fl�che gauche = droite */
                        if(Personnage_seDeplacer(perso,SDLK_RIGHT,niveau))
                        {
                            nb_tours++;
                            Niveau_ordonner(niveau);
                        }
                        break;

                    default:
                        break;
                }
             default:
                break;
        }
    }
}

void Item_rock(Niveau* niveau)
{
    srand(time(NULL)); /* initialisation de rand */
    unsigned int i= rand()%18; /* on g�n�re des coordonn�es al�atoires dans le but de trouver une pierre au hasard dans le niveau */
    unsigned int j= rand()%25;
    unsigned int nb_tentatives=0; /* Cette variable servira � sortir de la boucle si jamais plus aucuns rochers ne se trouve dans le niveau */
    while(niveau->grille[i][j]!=ROCHER) /* Tant qu'on ne trouve pas un rocher... */
    {
        while(nb_tentatives<3) /* On tente 3 fois de trouver un rocher*/
        {
            if(j<24) /* Si on n'est pas � l'avant derni�re colonne on passe � la suivante */
            {
                j++;
            }
            else if(j>=24 && i<17) /* Sinon si on est � la derni�re colonne mais pas � la derni�re ligne,
                                on va � la premi�re colonne de la ligne suivante */
            {
                j=0;
                i++;
            }
            else{ /* Sinon si on est arriv� � la derni�re colonne de la derni�re ligne, on retourne au d�but,
                c-�-d premi�re colonne de la premi�re ligne */
                j=0;
                i=0;
                nb_tentatives++; /* On incremente le nombre de tentatives vu que l'on retourne au d�but*/
            }
        }
    }
    if(nb_tentatives!=3) /* Si on a r�ussi � trouv� un rocher ... */
    {
        niveau->grille[i][j]=VIDE; /* On le fait disparaitre ... */
        Niveau_ordonner(niveau); /* Puis on ordonne le niveau */
    } /* Sinon on retourne simplement le niveau */
}

void Item_liberer(Item *item) {
    free(item);
}
