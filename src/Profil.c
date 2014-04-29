#include "../include/Profil.h"

void Profil_recupererPseudo(Profil* profil)
{
    SDL_Event Texte_Pour_Pseudo;
    int continuer=0, i=0;
    do
    {
         while(SDL_PollEvent(&Texte_Pour_Pseudo))
        {

            switch(Texte_Pour_Pseudo.type)
            {

            case SDL_KEYDOWN:// touche enfoncée :
                switch(Texte_Pour_Pseudo.key.keysym.sym)
                        {

                            case SDLK_a:
                            (*profil).nom[i++] = 'a';
                            break; // si lettre = a, alors on met la lettre a dans (*profil).nom[i]

                            case SDLK_b:
                            (*profil).nom[i++] = 'b';
                            break;

                            case SDLK_c:
                            (*profil).nom[i++] = 'c';
                            break;

                            case SDLK_d:
                            (*profil).nom[i++] = 'd';
                            break;

                            case SDLK_e:
                            (*profil).nom[i++] = 'e';
                            break;

                            case SDLK_f:
                            (*profil).nom[i++] = 'f';
                            break;

                            case SDLK_g:
                            (*profil).nom[i++] = 'g';
                            break;

                            case SDLK_h:
                            (*profil).nom[i++] = 'h';
                            break;

                            case SDLK_i:
                            (*profil).nom[i++] = 'i';
                            break;

                            case SDLK_j:
                            (*profil).nom[i++] = 'j';
                            break;

                            case SDLK_k:
                            (*profil).nom[i++] = 'k';
                            break;

                            case SDLK_l:
                            (*profil).nom[i++] = 'l';
                            break;

                            case SDLK_m:
                            (*profil).nom[i++] = 'm';
                            break;

                            case SDLK_n:

                            (*profil).nom[i++] = 'n';
                            break;

                            case SDLK_o:
                            (*profil).nom[i++] = 'o';
                            break;

                            case SDLK_p:
                            (*profil).nom[i++] = 'p';
                            break;

                            case SDLK_q:
                            (*profil).nom[i++] = 'q';
                            break;

                            case SDLK_r:
                            (*profil).nom[i++] = 'r';
                            break;

                             case SDLK_s:
                            (*profil).nom[i++] = 's';
                            break;

                             case SDLK_t:
                            (*profil).nom[i++] = 't';
                            break;

                             case SDLK_u:
                            (*profil).nom[i++] = 'u';
                            break;

                             case SDLK_v:
                            (*profil).nom[i++] = 'v';
                            break;

                             case SDLK_w:
                            (*profil).nom[i++] = 'w';
                            break;

                             case SDLK_x:
                            (*profil).nom[i++] = 'x';
                            break;

                             case SDLK_y:
                            (*profil).nom[i++] = 'y';
                            break;

                             case SDLK_z:
                            (*profil).nom[i++] = 'z';
                            break;


                            case SDLK_RETURN:
                            continuer = 1;
                            break;

                            default :
                            break;
                        }
                    break;

                default:
                break;
            }
        }

    }while(continuer != 1); // tant que l'user n'a pas préssé la touche ENTRER

}

Profil* Profil_creer(void)
{
    unsigned int id=Profil_prochainID();
    Profil* profil=malloc(sizeof(Profil));
    (*profil).identifiant=id;
    Profil_recupererPseudo(profil);

    FILE* fichier = fopen("../profil.base", "wb");

    unsigned int nb_enregistrements;
    fread(&nb_enregistrements,sizeof(unsigned int),1,fichier);
    fseek(fichier,0,SEEK_END);
    fwrite(&id,sizeof(unsigned int),1,fichier);
    fwrite((*profil).nom,sizeof(char[NOM_TAILLE_MAX]),1,fichier);
    fseek(fichier,0,SEEK_SET);
    nb_enregistrements++;
    fwrite(&nb_enregistrements,sizeof(unsigned int),1,fichier);

    fclose(fichier);
    return NULL;
}

void Profil_modifier(Profil *profil)
{
    unsigned int id;
    Profil_recupererPseudo(profil);

    FILE* fichier = fopen("../profil.base", "wb");
    fseek(fichier,sizeof(unsigned int),SEEK_SET);
    fread(&id,sizeof(unsigned int),1,fichier);
    while(id!=(*profil).identifiant){
        fseek(fichier,sizeof(char[20]),SEEK_CUR);
        fread(&id,sizeof(unsigned int),1,fichier);
    }
    fseek(fichier,sizeof(unsigned int),SEEK_CUR);
    fwrite((*profil).nom,sizeof(char[20]),1,fichier);

    fclose(fichier);
}

Profil* Profil_charger(FILE *fichier)
{
    return NULL;
}

void Profil_supprimer(Profil *profil)
{
    /*unsigned int nb_enregistrements, id;
    char nom[NOM_TAILLE_MAX];
    FILE* fichier = fopen("../profil.base", "w+b");

    fread(&nb_enregistrements,sizeof(unsigned int),1,fichier);
    fread(&id,sizeof(unsigned int),1,fichier);

    while(id!=(profil->identifiant))
    {
        fseek(fichier,sizeof(char)*(NOM_TAILLE_MAX+1),SEEK_CUR);
        fread(&id,sizeof(unsigned int),1,fichier);
    }

    fseek(fichier,sizeof(char)*(NOM_TAILLE_MAX+1),SEEK_CUR);

    while(fread(&id,sizeof(unsigned int),1,fichier)!=EOF)
    {
        fread(nom,sizeof(char)*(NOM_TAILLE_MAX+1),1,fichier)
        fseek(fichier,-2*((sizeof(char)*(NOM_TAILLE_MAX+1))+ sizeof(unsigned int)),SEEK_CUR);
        fwrite(&id,sizeof(unsigned int),1,fichier);
        fwrite(nom,sizeof(char)*(NOM_TAILLE_MAX+1),1,fichier);
        fseek(fichier,(sizeof(char)*(NOM_TAILLE_MAX+1))+ sizeof(unsigned int),SEEK_CUR);
    }

    fclose(fichier);*/

    unsigned int nb_enregistrements, id;
    char nom[NOM_TAILLE_MAX];
    FILE* fichier = fopen("../profil.base", "w+b");

    fread(&nb_enregistrements,sizeof(unsigned int),1,fichier);
    FILE* fichier2 = fopen("../profil2.base", "wb");
    fwrite(&nb_enregistrements,sizeof(unsigned int),1,fichier2);

    while(fread(&id,sizeof(unsigned int),1,fichier)!=(profil->identifiant))
    {
        fread(nom,sizeof(char)*(NOM_TAILLE_MAX+1),1,fichier);
        fwrite(&id,sizeof(unsigned int),1,fichier2);
        fwrite(nom,sizeof(char)*(NOM_TAILLE_MAX+1),1,fichier2);
    }
    fseek(fichier,sizeof(char)*(NOM_TAILLE_MAX+1),SEEK_CUR);

    while(fread(&id,sizeof(unsigned int),1,fichier)!=EOF)
    {
        fread(nom,sizeof(char)*(NOM_TAILLE_MAX+1),1,fichier);
        fwrite(&id,sizeof(unsigned int),1,fichier2);
        fwrite(nom,sizeof(char)*(NOM_TAILLE_MAX+1),1,fichier2);
    }

    fclose(fichier2);
    fclose(fichier);

    if(remove("../profil.base")!=0) printf("Erreur lors de la suppression");
    if(rename("../profil2.base","../profil.base")!=0)printf("Erreur lors du renommage");
}

unsigned int Profil_prochainID(void)
{
    unsigned int maxID = 0;
    unsigned int courrantID = maxID;

    FILE *fichier = fopen("../profil.base", "rb");

    if (fichier == NULL)
    {
        printf("Erreur [Profil_prochainId] : Ouverture de profil.base\n");
    }

    while (fread(&courrantID, sizeof(unsigned int), 1, fichier) != 0)
    {
        if (courrantID > maxID)
            maxID = courrantID;
    }

    fclose(fichier);

    return maxID+1;
}
