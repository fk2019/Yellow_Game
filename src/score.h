#ifndef SCORE_H
#define SCORE_H
#include "main.h"

typedef struct
{
	SDL_Renderer *renderer;
	SDL_Texture *image;
	TTF_Font *font;
	SDL_Color color;
	SDL_Rect rect;
	Uint32 score;
} Score;
bool score_new(Score **score, SDL_Renderer *renderer);
void score_free(Score **score);
bool score_reset(Score *s);
bool score_update(Score *s);
bool score_increment(Score *s);
void score_draw(Score *s);

#endif
