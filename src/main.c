#include "../include/Profil.h"
#include "../include/Partie.h"
#include "../include/Personnage.h"
#include "../include/Record.h"
#include "../include/Menu.h"
#include "../include/GererEntrees.h"

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>

int main(int argc, char *argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) == -1) // Démarrage de la SDL. Si erreur :
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); // Écriture de l'erreur
        exit(EXIT_FAILURE); // On quitte le programme
    }

    if(TTF_Init() == -1)
	{
	    fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
	    exit(EXIT_FAILURE);
	}

    /*FILE *fichier;

    fichier = fopen("profil/profil.base", "wb");

    unsigned int nb_enregistrements = 2;
    unsigned int nb=1;
    char nom[21] = {'M', 'i', 'c', 'h', 'e', 'l'};
    char nom2[21] = {'F', 'l', 'o'};
    fwrite(&nb_enregistrements, sizeof(unsigned int), 1, fichier);
    fwrite(&nb, sizeof(unsigned int), 1, fichier);
    fwrite(nom, sizeof(char)*21, 1, fichier);
    nb++;
    fwrite(&nb, sizeof(unsigned int), 1, fichier);
    fwrite(nom2, sizeof(char)*21, 1, fichier);*/

    SDL_Surface *ecran = NULL;
    SDL_Event event;
    SDL_Event event2;
    int loop = 1;

    ecran = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Digger", NULL);
    SDL_WM_SetIcon(IMG_Load("img/perso.png"), NULL);

    //Profil *profil = NULL;

    Profil_afficherListe(ecran);
    SDL_Flip(ecran);

    while (loop)
    {
        SDL_PollEvent(&event);

        switch (event.type)
        {
            case SDL_KEYDOWN:
                if(event.key.keysym.sym==SDLK_RETURN || event.key.keysym.sym==SDLK_ESCAPE)
                    loop=0;
                    break;

            case SDL_QUIT:
                loop = 0;
                break;

            default:
                break;
        }
    }

    GererEntrees_initialiser();
    Entree* entree=Entree_creer(NUM);
    GererEntrees_afficherEntree(entree,ecran);
    SDL_Flip(ecran);
    loop =1;

    while(loop)
    {
        SDL_PollEvent(&event2);

        switch(event2.type)
        {
        case SDL_KEYDOWN:
            if(event2.key.keysym.sym==SDLK_RETURN)
                loop=0;
            break;

        default:
            break;
        }
        GererEntrees_interface(entree,&event2);
        GererEntrees_afficherEntree(entree,ecran);
        SDL_Flip(ecran);
    }

    Profil* profil= Profil_charger(entree->num);

    if(profil!=NULL)
    {
        Menu *menu = NULL;
        menu = Menu_initialiser();

        Menu_ajouterOption(menu, JOUER);
        Menu_ajouterOption(menu, OPTIONS);
        Menu_ajouterOption(menu, QUITTER);

        Menu_derouler(menu, ecran, profil);


        Menu_liberer(menu);
    }

    else free(profil);

    TTF_Quit();
    SDL_Quit();

    return EXIT_SUCCESS;
}
