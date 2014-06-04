#include "../include/Partie.h"

Partie* Partie_creer(Profil *profil, Mode* mode)
{
    Partie* partie= (Partie*)malloc(sizeof(Partie));

    partie->profil= profil;
    partie->item= Item_initialiser();
    partie->mode= mode;
    partie->score= Score_initialiser(mode);
    partie->niveau= Niveau_charger(1);
    return partie;
}

Partie* Partie_charger(FILE *fichier)
{
    Partie *partie = (Partie*)malloc(sizeof(Partie));

    unsigned int indexProfil, indexNiveau;

    fread(&indexProfil, sizeof(unsigned int), 1, fichier);

    partie->profil = Profil_charger(indexProfil);
    fread(partie->item, sizeof(Item), 1, fichier);
    fread(partie->mode, sizeof(Mode), 1, fichier);
    fread(partie->score, sizeof(Score), 1, fichier);

    fread(&indexNiveau, sizeof(unsigned int), 1, fichier);

    partie->niveau = Niveau_charger(indexNiveau);

    fclose(fichier);

    return partie;
}

void Partie_sauvegarder(Partie *partie)
{
    char chemin[255];

    sprintf(chemin, "sauvegarde/%d-%d.sauv", partie->profil->identifiant, partie->niveau->index);

    FILE *fichier = fopen(chemin, "wb");

    fwrite(&(partie->profil->identifiant), sizeof(unsigned int), 1, fichier);
    fwrite(partie->item, sizeof(Item), 1, fichier);
    fwrite(partie->mode, sizeof(Mode), 1, fichier);
    fwrite(partie->score, sizeof(Score), 1, fichier);
    fwrite(&(partie->niveau->index), sizeof(unsigned int), 1, fichier);

    fclose(fichier);
}

void Partie_liberer(Partie *partie)
{
    Score_liberer(partie->score);
    Niveau_liberer(partie->niveau);
    Item_liberer(partie->item);
    free(partie);
}

void Partie_detruireSauv(Partie *partie) {
    char chemin[255];

    sprintf(chemin, "sauvegarde/%d-%d.sauv", partie->profil->identifiant, partie->niveau->index);

    remove(chemin);
}

int Partie_estFinie(Partie *partie) {
    int finie = 1;
    unsigned int i, j;

    for (i=0; finie && i < HAUTEUR; i++) {
        for (j=0; finie && j < LARGEUR; j++) {
            if (partie->niveau->grille[i][j] == FRUIT)
                finie = 0;
        }
    }
    return finie;
}

void Partie_derouler(Partie *partie, SDL_Surface *ecran) {
    SDL_Event event;
    SDL_Surface *perdu = NULL;
    SDL_Surface *gagne = NULL;

    SDL_Rect position;
	position.x = 0;
	position.y = 0;

    int loop = 1;

    Personnage personnage;

    Personnage_initialiser(&personnage, partie->niveau);

    while (loop)
        {
            if (Partie_estFinie(partie)) /*Si la partie est fini, i.e. on a ramassé tous les fruits ...*/
            {
                gagne=IMG_Load("img/gagne.png");
                SDL_BlitSurface(gagne, NULL, ecran, &position); /*On affiche l'image 'Gagné' et on sort de la boucle*/
                SDL_Flip(ecran);

                unsigned int attente=1;
                while(attente)
                {
                    SDL_PollEvent(&event);
                    switch(event.type) /*On attend que le joueur appuie sur une touche pour avoir le temps de voir l'image*/
                    {
                        case SDL_KEYDOWN:
                            attente=0;
                            break;
                        default:
                            break;
                    }
                }

                if(partie->niveau->index!=NB_NIVEAUX)
                {
                    Partie_prochainNiveau(partie, ecran);
                    Personnage_initialiser(&personnage,partie->niveau);
                }
                else loop=0;
            }

            else if(!Personnage_estVivant(&personnage, partie->niveau)) /*Si on est mort...*/
            {
                perdu=IMG_Load("img/perdu.png");
                SDL_BlitSurface(perdu, NULL, ecran, &position);/*on affiche l'image 'Perdu' et on sort de la boucle*/
                SDL_Flip(ecran);
                SDL_WaitEvent(&event);
                switch(event.type) /*On attend que le joueur appuie sur une touche pour avoir le temps de voir l'image*/
                {
                    case SDL_KEYDOWN:
                        loop=0;
                        break;
                    default:
                        break;
                }
                Partie_recommencerNiveau(partie,ecran);
                Personnage_initialiser(&personnage,partie->niveau);
            }

            else
            {
                SDL_PollEvent(&event);
                switch(event.type)
                {
                    case SDL_QUIT:
                    loop = 0;
                        break;
                    case SDL_KEYDOWN:
                        if(event.key.keysym.sym==SDLK_ESCAPE) /*Si on appuie sur Echap, on retourne au menu principal*/
                            loop=0;
                        if(event.key.keysym.sym==SDLK_s) /* Si on appuie sur S on sauvegarde la partie*/
                            Partie_sauvegarder(partie);
                        if(event.key.keysym.sym==SDLK_RETURN)/* Si on appuie sur Entree on recommence le niveau*/
                        {
                            Partie_recommencerNiveau(partie,ecran);
                            Personnage_initialiser(&personnage,partie->niveau);
                        }
                        else if (personnage.libre)
                            Personnage_seDeplacer(&personnage, event.key.keysym.sym, partie->niveau);
                        break;
                    default:
                    case SDL_KEYUP:
                        personnage.libre = 1;
                        break;
                }


            SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));

            Score_miseAJour(partie->score);
            Score_afficher(partie->score, ecran);
            Niveau_ordonner(partie->niveau);
            Niveau_afficher(partie->niveau, ecran);
            SDL_Flip(ecran);
            }
        }
}

unsigned int Partie_nbFruitsRestants(Partie *partie) {
    unsigned int nb = 0;

    unsigned int i, j;

    for (i=0; i < HAUTEUR; i++) {
        for (j=0; j < HAUTEUR; j++) {
            if (partie->niveau->grille[i][j] == FRUIT)
                nb++;
        }
    }

    return nb;
}

unsigned int Partie_nbPartie(void) {
    unsigned int taille = 0;

    DIR *rep = NULL;

    struct dirent *lecture = NULL;

    rep = opendir("sauvegarde");

    while ((lecture = readdir(rep))) {
        if (strcmp(lecture->d_name, ".") != 0 && strcmp(lecture->d_name, "..") != 0)
            taille++;
        /* On ne compte pas "." et "..". */
    }

    closedir(rep);

    return taille;
}

Partie** Partie_lister(void)
{
    Partie **liste = NULL;
    FILE *fichier;
    char chemin[255];
    unsigned int i = 0;

    liste = (Partie**)malloc(sizeof(Partie*)*Partie_nbPartie());

    struct dirent *lecture = NULL;

    DIR *rep;

    rep = opendir("sauvegarde");

    while ((lecture = readdir(rep))) {
        if (strcmp(lecture->d_name, ".") != 0 && strcmp(lecture->d_name, "..") != 0) {
            /* On ne compte pas "." et ".." qui apparaitront avec cette fonction */
            sprintf(chemin, "sauvegarde/%s.sauv", lecture->d_name);

            fichier = fopen(chemin, "rb");

            liste[i] = Partie_charger(fichier);

            fclose(fichier);

            i++;
        }
    }

    closedir(rep);

    return liste;
}

void Partie_libererListe(Partie **liste) {
    unsigned int nbPartie = Partie_nbPartie();
    unsigned int i;

    for (i=0; i < nbPartie; i++) {
        Partie_liberer(liste[i]);
    }

    free(liste);
}

void Partie_prochainNiveau(Partie* partie, SDL_Surface *ecran)
{
    unsigned int nouvelIndex=partie->niveau->index;
    nouvelIndex++;

    Score_liberer(partie->score);
    Niveau_liberer(partie->niveau);
    Item_liberer(partie->item);

    partie->score=Score_initialiser(partie->mode);
    partie->niveau=Niveau_charger(nouvelIndex);
    partie->item=Item_initialiser();

    Niveau_afficher(partie->niveau,ecran);
}

void Partie_recommencerNiveau(Partie* partie, SDL_Surface *ecran)
{
    unsigned int indexNiveau=partie->niveau->index;

    Score_liberer(partie->score);
    Niveau_liberer(partie->niveau);
    Item_liberer(partie->item);

    partie->score=Score_initialiser(partie->mode);
    partie->niveau=Niveau_charger(indexNiveau);
    partie->item=Item_initialiser();

    Niveau_afficher(partie->niveau,ecran);
}
