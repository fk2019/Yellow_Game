#include "initialize.h"

bool game_initialize(Game *g)
{
	if (SDL_Init(SDL_FLAGS))
	{
		fprintf(stderr, "Error initializing SDL2: %s\n", SDL_GetError());
		return true;
	}
	int img_init = IMG_Init(IMAGE_FLAGS);
	if ((img_init & IMAGE_FLAGS) != IMAGE_FLAGS)
	{
		fprintf(stderr, "Error initializing SDL_image: %s\n", IMG_GetError());
		return true;
	}
	int mix_init = Mix_Init(MIXER_FLAGS);
	if ((mix_init & MIXER_FLAGS) != MIXER_FLAGS)
	{
		fprintf(stderr, "Error initializing mixer: %s\n", Mix_GetError());
		return true;
	}

	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024))
	{
		fprintf(stderr, "Error opening audio: %s\n", Mix_GetError());
		return true;
	}
		
	g->window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
	if (!g->window)
	{
		fprintf(stderr, "Error creating window: %s\n", SDL_GetError());
		return true;
	}
	g->renderer = SDL_CreateRenderer(g->window, -1, SDL_RENDERER_ACCELERATED);
	if (!g->renderer)
	{
		fprintf(stderr, "Error creating renderer: %s\n", SDL_GetError());
		return true;
	}

	SDL_Surface *icon_surf = IMG_Load(WINDOW_ICON);
	if (icon_surf)
	{
		SDL_SetWindowIcon(g->window, icon_surf);
		SDL_FreeSurface(icon_surf);
		icon_surf = NULL;
	} else
	{
		fprintf(stderr, "Error loading icon surface: %s\n", IMG_GetError());
		return true;
	}
	
	srand((unsigned)time(NULL));
	return false;
}
