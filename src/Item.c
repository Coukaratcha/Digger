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

Personnage* Item_force(Personnage* perso, Niveau* niveau)
{
    return perso;
}

Niveau* Item_flashback(Niveau* niveau, Bloc** grilleSauv)
{
    unsigned int i;
    unsigned int j;

    for(i=0;i<18;i++)
    {
        for(j=0;j<25;j++)
        {
            niveau->grille[i][j]=grilleSauv[i][j];
        }
    }

    return niveau;
}

Personnage* Item_keyswitch(Personnage *perso, Niveau* niveau)
{
    SDL_Event event;
    unsigned int nb_tours=0;
    unsigned int postemp=0;

    while(nb_tours<10)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_UP: // Flèche haut = gauche
                        postemp=perso->posx;
                        if(postemp-32>=0 && Personnage_seDeplacer(perso))
                        {
                            perso->posx-=32;
                            nb_tours++;
                            Niveau_ordonner(niveau);
                        }
                        break;

                    case SDLK_DOWN: // Flèche bas = haut
                        postemp=perso->posy;
                        if(postemp-32>=0 && Personnage_seDeplacer(perso))
                        {
                            perso->posy-=32;
                            nb_tours++;
                            Niveau_ordonner(niveau);
                        }
                        break;

                    case SDLK_RIGHT: // Flèche droite = bas
                        postemp=perso->posy;
                        if(postemp+32<576 && Personnage_seDeplacer(perso)) // 576=32*18
                        {
                            perso->posy+=32;
                            nb_tours++;
                            Niveau_ordonner(niveau);
                        }
                        break;

                    case SDLK_LEFT: // Flèche gauche = droite
                        postemp=perso->posx;
                        if(postemp+32<800 && Personnage_seDeplacer(perso)) // 800=32*25
                        {
                            perso->posx+=32;
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
    return perso;
}

Niveau* Item_rock(Niveau* niveau)
{
    srand(time(NULL)); /* initialisation de rand */
    unsigned int i= rand()%18; /* on génère des coordonnées aléatoires dans le but de trouver une pierre au hasard dans le niveau */
    unsigned int j= rand()%25;
    unsigned int nb_tentatives=0; /* Cette variable servira à sortir de la boucle si jamais plus aucuns rocher ne se trouve dans le niveau */
    while(niveau->grille[i][j]!=ROCHER) /* Tant qu'on ne trouve pas un rocher... */
    {
        while(nb_tentatives<3) /* On tente 3 fois de trouver un rocher*/
        {
            if(j<24) /* Si on n'est pas à l'avant dernière colonne on passe à la suivante */
            {
                j++;
            }
            else if(j>=24 && i<17) /* Sinon si on est à la dernière colonne mais pas à la dernière ligne,
                                on va à la première colonne de la ligne suivante */
            {
                j=0;
                i++;
            }
            else{ /* Sinon si on est arrivé à la dernière colonne de la dernière ligne, on retourne au début,
                c-à-d première colonne de la première ligne */
                j=0;
                i=0;
                nb_tentatives++; /* On incremente le nombre de tentatives vu que l'on retourne au début*/
            }
        }
    }
    if(nb_tentatives!=3) /* Si on a réussi à trouvé un rocher ... */
    {
        niveau->grille[i][j]=VIDE; /* On le fait disparaitre ... */
        Niveau_ordonner(niveau); /* Puis on ordonne le niveau */
    } /* Sinon on retourne simplement le niveau */
    return niveau;
}

void Item_liberer(Item *item) {
    free(item);
}
