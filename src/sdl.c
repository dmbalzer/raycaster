#include "sdl.h"
#include "defs.h"
#include <stdlib.h>
#include <stdio.h>

static SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
static bool window_closed = false;
float frametime = 0.0f;
bool* keystate = NULL;

void sdl_init(void)
{
	if ( !SDL_Init(SDL_INIT_VIDEO) ) {
		fprintf(stderr, "%s\n", SDL_GetError());
		exit(1);
	}
	if ( !SDL_CreateWindowAndRenderer("Raycaster", WIN_W, WIN_H, 0, &window, &renderer) ) {
		fprintf(stderr, "%s\n", SDL_GetError());
		exit(1);
	}
	SDL_SetRenderVSync(renderer, 1);
	keystate = (bool*)SDL_GetKeyboardState(NULL);
}

void sdl_process_events(void)
{
	SDL_Event ev;
	while ( SDL_PollEvent(&ev) ) {
		switch ( ev.type ) {
			case SDL_EVENT_QUIT:
				window_closed = true;
			break;
			case SDL_EVENT_KEY_DOWN:
				if ( ev.key.key == SDLK_ESCAPE ) window_closed = true;
			break;
		}
	}
}

bool sdl_window_closed(void)
{
	return window_closed;
}

void sdl_begin_drawing(void)
{
	SDL_SetRenderDrawColor(renderer, BLACK);
	SDL_RenderClear(renderer);
}

void sdl_end_drawing(void)
{
	SDL_RenderPresent(renderer);
	static Uint64 prev = 0;
	const Uint64 now = SDL_GetTicks();
	frametime = ( now - prev ) / 1000.0f;
	prev = now;
}

void sdl_unload(void)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
