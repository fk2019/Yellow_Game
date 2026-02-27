#include "player.h"

bool player_new(Player **player, SDL_Renderer *renderer, SDL_Texture *image)
{
	*player = calloc(1, sizeof(Player));
	if (*player == NULL)
	{
		fprintf(stderr, "Error in calloc of player.\n");
		return true;
	}
	Player *p = *player;
	p->renderer = renderer;
	p->image = image;
	p->keystate = SDL_GetKeyboardState(NULL);
	p->speed = 5;
	p->top_offset = 10;
	p->left_offset = 47;
	p->right_offset = 43;
	
	if (SDL_QueryTexture(p->image, NULL, NULL,& p->rect.w, &p->rect.h))
	{
		fprintf(stderr, "Error querying player texture: %s\n", SDL_GetError());
		return true;
	}
	player_reset(p);
	p->rect.y = 337;
	return false;
	
}
void player_free(Player **player)
{
	if (*player)
	{
		(*player)->image = NULL;
		(*player)->renderer = NULL;
		(*player)->keystate = NULL;
		free(*player);
		*player = NULL;
	}
}

void player_draw(Player *p)
{
	SDL_RenderCopyEx(p->renderer, p->image, NULL, &p->rect, 0, NULL, p->flip);
}
void player_reset(Player *p)
{
	p->flip = SDL_FLIP_NONE;
	p->rect.x = (WINDOW_WIDTH - p->rect.w) / 2;
}
int player_top(Player *p)
{
	return p->rect.y + p->top_offset;
}
int player_left(Player *p)
{
	return p->rect.x + p->left_offset;
}
int player_right(Player *p)
{
	return p->rect.x + p->rect.w - p->right_offset;
}
void player_update(Player *p)
{
	if (p->keystate[SDL_SCANCODE_LEFT])
	{
		p->rect.x -= p->speed;
		if (p->rect.x <= 0)
		{
			p->rect.x = 0;
		}
		p->flip = SDL_FLIP_HORIZONTAL;
	}
	if (p->keystate[SDL_SCANCODE_RIGHT])
	{
		p->rect.x += p->speed;
		if ((p->rect.x + p->rect.w) >= WINDOW_WIDTH)
		{
			p->rect.x = WINDOW_WIDTH - p->rect.w;
		}
		p->flip = SDL_FLIP_NONE;
	}
}
