#include "game.h"
#include "initialize.h"
#include "load_media.h"
#include "flakes.h"

bool check_collision(Game *g);
bool handle_collision(Game *g, Flake *f);
bool game_reset(Game *g);

bool game_new(Game **game)
{
	*game = calloc(1, sizeof(Game));
	if (*game == NULL)
	{
		fprintf(stderr, "Error in calloc of new game.\n");
		return true;
	}
	Game *g = *game;
	if (game_initialize(g)) return true;
	if (game_load_media(g)) return true;
	if (player_new(&g->player, g->renderer, g->player_image)) return true;
	for (int i = 0; i < 5; ++i)
	{
		if (flake_new(&g->flakes, g->renderer, g->yellow_image, false)) return true;
	}
	for (int i = 0; i < 10; ++i)
	{
		if (flake_new(&g->flakes, g->renderer, g->white_image, true)) return true;
	}
	g->playing = true;
	
	return false;
}

void game_free(Game **game)
{
	
	if (*game)
	{
		Game *g = *game;
		flakes_free(&g->flakes);
		player_free(&g->player);

		Mix_FreeChunk(g->collect_sound);
		g->collect_sound = NULL;
		Mix_FreeChunk(g->hit_sound);
		g->hit_sound = NULL;
		
		SDL_DestroyTexture(g->yellow_image);
		g->yellow_image = NULL;
		SDL_DestroyTexture(g->white_image);
		g->white_image = NULL;
		SDL_DestroyTexture(g->player_image);
		g->player_image = NULL;
		
		SDL_DestroyTexture(g->background_image);
		g->background_image = NULL;
		SDL_DestroyRenderer(g->renderer);
		g->renderer = NULL;
		SDL_DestroyWindow(g->window);
		g->window = NULL;

		Mix_CloseAudio();
		
		Mix_Quit();
		IMG_Quit();
		SDL_Quit();
		free(g);
		g = NULL;
		*game = NULL;
	}
	
}

bool game_reset(Game *g)
{
	flakes_reset(g->flakes);
	player_reset(g->player);
	g->playing = true;
	return false;
}
bool handle_collision(Game *g, Flake *f)
{
	if (f->is_white){
		Mix_PlayChannel(-1, g->collect_sound, 0);
		flake_reset(f, false);
	} else
	{
		Mix_PlayChannel(-1, g->hit_sound, 0);
		flake_reset(f, false);
		g->playing = false;
	}
	return false;
}
bool check_collision(Game *g)
{
	Flake *f = g->flakes;
	int p_top = player_top(g->player);
	int p_left = player_left(g->player);
	int p_right = player_right(g->player);

	while (f)
	{
		if (flake_bottom(f) > p_top)
		{
			if (flake_right(f) > p_left)
			{
				if (flake_left(f) < p_right)
				{
					if(handle_collision(g, f)) return true;
				}
			}
		}
		f = f->next;
	}
	return false;
}

bool game_run(Game *g)
{
	while(true)
	{
		while (SDL_PollEvent(&g->event))
		{
			switch(g->event.type)
			{
			case SDL_QUIT:
				return false;
				break;
			case SDL_KEYDOWN:
				switch(g->event.key.keysym.scancode)
				{
				case SDL_SCANCODE_ESCAPE:
					return false;
					break;
				case SDL_SCANCODE_SPACE:
					if (!g->playing)
					{
						if (game_reset(g)) return true;
					}
				default:
					break;
				}
			default:
				break;
			}
		}
		if (g->playing)
		{
			player_update(g->player);
			flakes_update(g->flakes);
			if (check_collision(g)) return true;
		}
		SDL_RenderClear(g->renderer);
		//draw
		SDL_RenderCopy(g->renderer, g->background_image, NULL, &g->background_rect);
		player_draw(g->player);
		flakes_draw(g->flakes);
		SDL_RenderPresent(g->renderer);

		SDL_Delay(16);
	}
	return false;
}
