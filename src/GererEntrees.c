#include "../include/GererEntrees.h"

TTF_Font *policeGE = NULL;
SDL_Color blancGE = {255, 255, 255};
int libre = 1;

Entree* Entree_creer(TypeEntree type) {
	Entree *entree = (Entree*)malloc(sizeof(Entree));

	entree->type = type;
	entree->surfaceCurrent = NULL;
	entree->surfaceTexte = NULL;
	entree->fin = 0;

	if (type == TEXTE) {
		entree->current = 'A';
		memset(entree->texte, '\0', TEXTE_TAILLE_MAX+1);
		entree->surfaceCurrent = TTF_RenderText_Blended(policeGE, "A", blancGE);
		entree->surfaceTexte = TTF_RenderText_Blended(policeGE, "", blancGE);
	}
	else if (type == NUM) {
		entree->num = 0;
		entree->surfaceCurrent = TTF_RenderText_Blended(policeGE, "0", blancGE);
	}

	return entree;
}

void Entree_liberer(Entree *entree) {
	SDL_FreeSurface(entree->surfaceCurrent);
	if (entree->type == TEXTE) {
		SDL_FreeSurface(entree->surfaceTexte);
	}
	free(entree);
}

void GererEntrees_initialiser(void) {
	policeGE = TTF_OpenFont("fonts/orangejuice.ttf", 30);
}



void GererEntrees_interface(Entree *entree, SDL_Event *event) {
	switch (event->type) {
		case SDL_KEYDOWN:
			if (libre) {
				if (entree->type == TEXTE) {
					if (event->key.keysym.sym == SDLK_SPACE) {
						GererEntrees_ajouterCar(entree);
					}
					else if (event->key.keysym.sym == SDLK_BACKSPACE) {
						GererEntrees_supprimerCar(entree);
					}
					else if (event->key.keysym.sym == SDLK_RETURN) {
						entree->fin = 1;
					}
					else {
						GererEntrees_changerCar(event->key.keysym.sym, entree);
					}
				}
				else if (entree->type == NUM) {
					if (event->key.keysym.sym == SDLK_RETURN) {
						entree->fin = 1;
					}
					else {
						GererEntrees_changerNum(event->key.keysym.sym, entree);
					}
				}
			}
			libre = 0;
			break;
		case SDL_KEYUP:
			libre = 1;
			break;
	}
}

void GererEntrees_changerNum(SDLKey touche, Entree *entree) {
	switch(touche) {
		case SDLK_UP:
			entree->num++;
			break;
		case SDLK_DOWN:
			if (entree->num > 0) {
				entree->num--;
			}
			break;
		default:
			break;
	}
}

void GererEntrees_changerCar(SDLKey touche, Entree *entree) {
	switch(touche) {
		case SDLK_RIGHT:
			if (entree->current < 'Z') {
				entree->current++;
			}
			break;
		case SDLK_LEFT:
			if (entree->current > 'A') {
				entree->current--;
			}
			break;
		default:
			break;
	}
}

void GererEntrees_afficherEntree(Entree *entree, SDL_Surface *ecran) {
	if (entree->type == NUM) {
		GererEntrees_afficherNum(entree, ecran);
	}
	else if (entree->type == TEXTE) {
		GererEntrees_afficherCar(entree, ecran);
		GererEntrees_afficherText(entree, ecran);
	}
}

void GererEntrees_afficherNum(Entree *entree, SDL_Surface *ecran) {
	char temp[TEXTE_TAILLE_MAX+1];

	SDL_Rect position;
	position.x = 400;
	position.y = 100;

	sprintf(temp, "%d", entree->num);

	SDL_FreeSurface(entree->surfaceCurrent);

	entree->surfaceCurrent = TTF_RenderText_Blended(policeGE, temp, blancGE);

	SDL_BlitSurface(entree->surfaceCurrent, NULL, ecran, &position);
}

void GererEntrees_afficherCar(Entree *entree, SDL_Surface *ecran) {
	char temp[TEXTE_TAILLE_MAX+1];

	SDL_Rect position;
	position.x = 400;
	position.y = 100;

	sprintf(temp, "%c", entree->current);

	SDL_FreeSurface(entree->surfaceCurrent);

	entree->surfaceCurrent = TTF_RenderText_Blended(policeGE, temp, blancGE);

	SDL_BlitSurface(entree->surfaceCurrent, NULL, ecran, &position);
}

void GererEntrees_afficherText(Entree *entree, SDL_Surface *ecran) {
	SDL_Rect position;

	position.x = 300;
	position.y = 200;

	SDL_BlitSurface(entree->surfaceTexte, NULL, ecran, &position);
}

void GererEntrees_ajouterCar(Entree *entree) {
	unsigned int taille = strlen(entree->texte);

	if (taille < TEXTE_TAILLE_MAX + 1) {
		entree->texte[taille] = entree->current;
	}

	SDL_FreeSurface(entree->surfaceTexte);
	entree->surfaceTexte = TTF_RenderText_Blended(policeGE, entree->texte, blancGE);
}

void GererEntrees_supprimerCar(Entree *entree) {
	unsigned int taille = strlen(entree->texte);

	if (taille > 0){
		entree->texte[taille-1] = '\0';
	}

	SDL_FreeSurface(entree->surfaceTexte);
	entree->surfaceTexte = TTF_RenderText_Blended(policeGE, entree->texte, blancGE);
}

void GererEntrees_liberer(void) {
	TTF_CloseFont(policeGE);
}
