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
    if (SDL_Init(SDL_INIT_VIDEO) == -1) // Démarrage de la SDL. Si erreur :
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); // Écriture de l'erreur
        exit(EXIT_FAILURE); // On quitte le programme
    }

/////////////////////////AFFICHAGE DU MENU//////////////////////////////////////


/////////////////////////SWITCH SUIVANT CHOIX DU MENU////////////////////////////


/////////////////////////////////////////////////////////////////////////////////

    SDL_Quit();

    return 0;
}
