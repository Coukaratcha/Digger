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
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) == -1) // D�marrage de la SDL. Si erreur :
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); // �criture de l'erreur
        exit(EXIT_FAILURE); // On quitte le programme
    }

    if(TTF_Init() == -1)
	{
	    fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
	    exit(EXIT_FAILURE);
	}

    /*FILE *fichier;

    fichier = fopen("profil/profil.base", "wb");

    unsigned int nb = 1;
    char nom[21] = {'M', 'i', 'c', 'h', 'e', 'l'};

    fwrite(&nb, sizeof(unsigned int), 1, fichier);
    fwrite(&nb, sizeof(unsigned int), 1, fichier);
    fwrite(nom, sizeof(char)*21, 1, fichier);*/

    SDL_Surface *ecran = NULL;
    SDL_Event event;
    int loop = 1;

    ecran = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);

    GererEntrees_initialiser();

    Entree *entree = NULL;

    entree = Entree_creer(TEXTE);

    while (loop) {
        SDL_PollEvent(&event);

        switch (event.type) {
            case SDL_QUIT:
                loop = 0;
                break;
            default:
                break;
        }

        GererEntrees_derouler(ecran, entree, &event);

        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 25, 25, 25));
        GererEntrees_afficherEntree(entree, ecran);
        SDL_Flip(ecran);
    }

    Entree_liberer(entree);

    GererEntrees_liberer();

    /*Menu *menu = NULL;

    menu = Menu_initialiser();

    Menu_ajouterOption(menu, JOUER);
    Menu_ajouterOption(menu, OPTIONS);
    Menu_ajouterOption(menu, QUITTER);

    Menu_derouler(menu, ecran);*/

    /*Bloc grille[18][25] = {
    	{FRUIT, FRUIT, FRUIT, ROCHER, ROCHER, ROCHER, ROCHER, HERBE, HERBE, MUR, FRUIT, FRUIT, FRUIT, FRUIT, FRUIT, FRUIT, MUR, FRUIT, ROCHER, MUR, HERBE, HERBE, HERBE, HERBE, FRUIT},
    	{FRUIT, FRUIT, ROCHER, ROCHER, ROCHER, ROCHER, HERBE, HERBE, HERBE, MUR, FRUIT, FRUIT, FRUIT, FRUIT, FRUIT, FRUIT, MUR, FRUIT, ROCHER, MUR, HERBE, HERBE, HERBE, MUR, FRUIT},
    	{FRUIT, ROCHER, ROCHER, ROCHER, ROCHER, HERBE, HERBE, HERBE, HERBE, MUR, ROCHER, ROCHER, ROCHER, ROCHER, ROCHER, ROCHER, MUR, FRUIT, ROCHER, MUR, HERBE, HERBE, HERBE, MUR, FRUIT},
    	{ROCHER, ROCHER, ROCHER, ROCHER, HERBE, HERBE, HERBE, HERBE, HERBE, MUR, ROCHER, ROCHER, ROCHER, ROCHER, ROCHER, ROCHER, MUR, FRUIT, ROCHER, MUR, HERBE, HERBE, HERBE, MUR, FRUIT},
    	{ROCHER, ROCHER, ROCHER, HERBE, HERBE, HERBE, HERBE, HERBE, HERBE, MUR, HERBE, ROCHER, HERBE, HERBE, HERBE, HERBE, MUR, FRUIT, ROCHER, MUR, HERBE, HERBE, HERBE, MUR, FRUIT},
    	{ROCHER, ROCHER, HERBE, HERBE, ROCHER, ROCHER, ROCHER, HERBE, HERBE, MUR, HERBE, ROCHER, HERBE, HERBE, HERBE, HERBE, MUR, FRUIT, ROCHER, MUR, ROCHER, ROCHER, ROCHER, ROCHER, ROCHER},
    	{ROCHER, HERBE, HERBE, HERBE, ROCHER, ROCHER, ROCHER, HERBE, HERBE, MUR, HERBE, ROCHER, HERBE, HERBE, ROCHER, HERBE, MUR, FRUIT, ROCHER, MUR, HERBE, HERBE, HERBE, HERBE, HERBE},
    	{HERBE, HERBE, HERBE, HERBE, FRUIT, FRUIT, FRUIT, HERBE, HERBE, MUR, HERBE, ROCHER, HERBE, HERBE, ROCHER, HERBE, MUR, FRUIT, ROCHER, MUR, HERBE, HERBE, HERBE, HERBE, HERBE},
    	{HERBE, HERBE, HERBE, HERBE, HERBE, HERBE, HERBE, HERBE, HERBE, MUR, HERBE, ROCHER, HERBE, HERBE, ROCHER, MUR, MUR, FRUIT, ROCHER, MUR, HERBE, HERBE, HERBE, HERBE, HERBE},
    	{ROCHER, ROCHER, ROCHER, ROCHER, ROCHER, ROCHER, ROCHER, ROCHER, HERBE, MUR, HERBE, ROCHER, HERBE, HERBE, MUR, MUR, ROCHER, FRUIT, ROCHER, HERBE, HERBE, HERBE, HERBE, HERBE, HERBE},
    	{HERBE, HERBE, FRUIT, FRUIT, FRUIT, HERBE, HERBE, HERBE, HERBE, MUR, HERBE, HERBE, HERBE, HERBE, HERBE, HERBE, HERBE, HERBE, HERBE, HERBE, HERBE, HERBE, HERBE, HERBE, HERBE},
    	{HERBE, HERBE, HERBE, HERBE, HERBE, HERBE, HERBE, HERBE, HERBE, MUR, MUR, MUR, MUR, HERBE, HERBE, HERBE, MUR, MUR, MUR, MUR, MUR, MUR, HERBE, HERBE, MUR},
    	{HERBE, HERBE, HERBE, HERBE, HERBE, HERBE, HERBE, HERBE, HERBE, MUR, ROCHER, ROCHER, ROCHER, ROCHER, ROCHER, ROCHER, ROCHER, ROCHER, ROCHER, ROCHER, ROCHER, ROCHER, ROCHER, ROCHER, ROCHER},
    	{MUR, MUR, MUR, MUR, MUR, MUR, MUR, MUR, HERBE, MUR, HERBE, HERBE, HERBE, HERBE, HERBE, HERBE, MUR, ROCHER, FRUIT, FRUIT, ROCHER, MUR, HERBE, HERBE, HERBE},
    	{FRUIT, FRUIT, FRUIT, FRUIT, FRUIT, FRUIT, FRUIT, MUR, HERBE, MUR, HERBE, HERBE, HERBE, HERBE, HERBE, HERBE, MUR, ROCHER, ROCHER, ROCHER, ROCHER, MUR, HERBE, HERBE, HERBE},
    	{ROCHER, ROCHER, ROCHER, ROCHER, ROCHER, ROCHER, ROCHER, MUR, HERBE, MUR, HERBE, HERBE, HERBE, HERBE, HERBE, HERBE, MUR, MUR, HERBE, HERBE, MUR, MUR, HERBE, HERBE, HERBE},
    	{HERBE, HERBE, HERBE, HERBE, HERBE, HERBE, HERBE, HERBE, HERBE, MUR, HERBE, HERBE, HERBE, HERBE, PERSO, HERBE, HERBE, HERBE, HERBE, HERBE, HERBE, HERBE, HERBE, HERBE, HERBE},
    	{HERBE, HERBE, HERBE, HERBE, HERBE, HERBE, HERBE, HERBE, HERBE, HERBE, HERBE, HERBE, HERBE, HERBE, HERBE, HERBE, HERBE, HERBE, HERBE, HERBE, HERBE, HERBE, HERBE, HERBE, HERBE}
    };*/


    /*Menu_liberer(menu);*/
    TTF_Quit();
    SDL_Quit();

    return 0;
}
