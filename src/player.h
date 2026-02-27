#ifndef PLAYER_H
#define PLAYER_H

#include "main.h"
typedef struct
{
	SDL_Renderer *renderer;
	SDL_Texture *image;
	SDL_Rect rect;
	const Uint8 *keystate;
	SDL_RendererFlip flip;
	int speed;
	int top_offset;
	int right_offset;
	int left_offset;
} Player;

bool player_new(Player **player, SDL_Renderer *renderer, SDL_Texture *image);
void player_free(Player **player);
void player_update(Player *p);
void player_draw(Player *p);
int player_left(Player *p);
int player_right(Player *p);
int player_top(Player *p);
void player_reset(Player *p);
	
#endif
