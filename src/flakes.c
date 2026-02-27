#include "flakes.h"

bool flake_new(Flake **flake, SDL_Renderer *renderer, SDL_Texture *image, bool is_white)
{
	Flake *new_flake = calloc(1, sizeof(Flake));
	if(new_flake == NULL)
	{
		fprintf(stderr, "Error in calloc of flake.\n");
		return true;
	}
	new_flake->image = image;
	new_flake->renderer = renderer;
	new_flake->speed = 5;
	new_flake->ground = 490;
	new_flake->is_white = is_white;
	if (SDL_QueryTexture(new_flake->image, NULL, NULL, &new_flake->rect.w, &new_flake->rect.h))
	{
		fprintf(stderr, "Error querying flake: %s\n", SDL_GetError());
		return true;
	}
	new_flake->rect.x = rand() % (WINDOW_WIDTH - new_flake->rect.w);
	flake_reset(new_flake, true);
	new_flake->next = *flake;
	*flake = new_flake;
	return false;
}

void flakes_draw(Flake *f)
{
	while(f)
	{
		SDL_RenderCopy(f->renderer, f->image, NULL, &f->rect);
		f = f->next;
	}
}

void flakes_free(Flake **flakes)
{
	Flake *f = *flakes;
	while (f)
	{
		Flake *next = f->next;
		f->image = NULL;
		f->renderer = NULL;
		f->next = NULL;
		free(f);
		f = next;
	}
	*flakes = NULL;
}
int flake_left(Flake *f)
{
	return f->rect.x;
}
int flake_right(Flake *f)
{
	return f->rect.x + f->rect.w;
}
int flake_bottom(Flake *f)
{
	return f->rect.y + f->rect.h;
}
void flakes_update(Flake *f)
{
	while(f)
	{
		f->rect.y += f->speed;
		if (f->rect.y > f->ground)
		{
			flake_reset(f, false);
		}
		f = f->next;
	}
}

void flake_reset(Flake *f, bool full)
{
	int height = full ? WINDOW_HEIGHT *2: WINDOW_HEIGHT;
	f->rect.y = -(rand() % height) + f->rect.h;
	f->rect.x = rand() % (WINDOW_WIDTH - f->rect.w);
}

void flakes_reset(Flake *f)
{
	while(f)
	{
		flake_reset(f, true);
		f = f->next;
	}
}
