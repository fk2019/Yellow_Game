#ifndef FLAKES_H
#define FLAKES_H

#include "main.h"

typedef struct Flake
{
	struct Flake *next;
	SDL_Renderer *renderer;
	SDL_Texture *image;
	SDL_Rect rect;
	int speed;
	int ground;
	bool is_white;
} Flake;

bool flake_new (Flake **flake, SDL_Renderer *renderer, SDL_Texture *image, bool is_white);
void flakes_free(Flake **flakes);
void flakes_update(Flake *f);
void flakes_draw(Flake *f);
void flake_reset(Flake *f, bool full);
void flakes_reset(Flake *f);
int flake_left(Flake *f);
int flake_right(Flake *f);
int flake_bottom(Flake *f);
#endif
