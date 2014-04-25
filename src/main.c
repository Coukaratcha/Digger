#include "../include/Profil.h"
#include "../include/Partie.h"
#include "../include/Personnage.h"
#include "../include/Record.h"
#include "../include/Menu.h"
#include <SDL/SDL.h>

int main(int argc, char *argv[])
{
    FILE *fichier = fopen("/home/mickael/ProjetsC/Digger/profil/profil.base", "wb");

    fclose(fichier);

    printf("%u\n", Profil_prochainID());

    return 0;
}
