#ifndef FPS_H
#define FPS_H

#include "main.h"

typedef struct
{
	Uint32 last_time;
	double target_delay;
	double cap_delay;
	double carry_delay;
	double delta_time;
	Uint32 fps_last_time; //actual timestamp
	Uint32 fps_counter; //frame counter
	bool fps_display;
} Fps;
bool fps_new(Fps **fps);
void fps_free(Fps **fps);
void fps_toggle_display(Fps *f);
double fps_update(Fps *f);
#endif
