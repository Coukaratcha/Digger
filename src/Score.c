#include "../include/Score.h"

TTF_Font *police = NULL;
SDL_Color blanc = {255, 255, 255};

Score* Score_initialiser(Mode *mode)
{
    Score *score = (Score*)malloc(sizeof(Score));

    score->mode.type = mode->type;

    score->pas = 0;
    score->temps = SDL_GetTicks()/1000;

    police = TTF_OpenFont("../../fonts/coolvetica.ttf", 20);

    score->texte = TTF_RenderText_Solid(police, "0", blanc);

    return score;
}

void Score_augmenter(Score *score, int points)
{
	if (score->pas + points > 0)
		score->pas+=points;
	else
		score->pas = 0;
}

void Score_miseAJour(Score *score)
{
	char temp[255];

	if (score->mode.type == MONTRE) {
		unsigned int heures;
		unsigned int minutes;
		unsigned int secondes;
		unsigned int tempsEcoule = SDL_GetTicks()/1000 - score->temps;

		heures = tempsEcoule/3600;
		minutes = (tempsEcoule - heures*3600)/60;
		secondes = tempsEcoule - minutes*60 - heures*3600;

		sprintf(temp, "%d : %d : %d", heures, minutes, secondes);
	}
	else {
		sprintf(temp, "%d", score->pas);
	}

	score->texte = TTF_RenderText_Solid(police, temp, blanc);
}

void Score_afficher(Score *score, SDL_Surface *ecran) {
	SDL_Rect position;

	position.x = 400 - score->texte->w/2;
	position.y = 0;

	SDL_BlitSurface(score->texte, NULL, ecran, &position);
}

void Score_detruire(Score *score) {
	SDL_FreeSurface(score->texte);
	free(score);
	TTF_CloseFont(police);
}
