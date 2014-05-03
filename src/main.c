#include "../include/Profil.h"
#include "../include/Partie.h"
#include "../include/Personnage.h"
#include "../include/Record.h"
#include "../include/Menu.h"

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

    SDL_Event event;
    int loop = 1;

    SDL_Surface *ecran = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);

    FILE *fichier = fopen("../../niveau/1.niveau", "rb");

    if (fichier == NULL)
    	printf("Erreur ouverture fichier.\n");
    else
    	printf("Fichier ouvert correctement.\n");

    Niveau *niveau;

    niveau = Niveau_charger(fichier);

    Niveau_afficher(niveau, ecran);

    Mode *mode = Mode_creer();
    Mode_assignerMode(mode, BONUS);
    Score *score = Score_initialiser(mode);

    while(loop) {

    	SDL_PollEvent(&event);

    	switch(event.type) {
    		case SDL_QUIT:
    			loop = 0;
    			break;
    		default:
    			break;
    	}

    	SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
    	Score_miseAJour(score);
    	Score_afficher(score, ecran);
    	Niveau_afficher(niveau, ecran);
    	SDL_Flip(ecran);
    }

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

    fclose(fichier);

    TTF_Quit();
    SDL_Quit();

    return 0;
}
