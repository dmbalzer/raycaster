#include "defs.h"
#include "sdl.h"
#include <SDL3/SDL.h>

static SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
extern bool quit;
float frametime = 0.0f;

void sdl_init(void)
{
	if ( !SDL_Init(SDL_INIT_VIDEO) )
	{
		SDL_Log("%s", SDL_GetError()); exit(-1);
	}
	
	if ( !SDL_CreateWindowAndRenderer("Raycaster", WINDOW_W, WINDOW_H, 0, &window, &renderer) )
	{
		SDL_Log("%s", SDL_GetError()); exit(-1);
	}

	if ( !SDL_SetRenderVSync(renderer, 1) )
	{
		SDL_Log("%s", SDL_GetError()); exit(-1);
	}
}

void sdl_do_events(void)
{
	SDL_Event ev;
	while ( SDL_PollEvent(&ev) )
	{
		switch ( ev.type )
		{
			case SDL_EVENT_QUIT:
				quit = true;
			break;
		}
	}
}

void sdl_begin_draw(void)
{
	SDL_SetRenderDrawColor(renderer, BLACK);
	SDL_RenderClear(renderer);
}

void sdl_end_draw(void)
{
	SDL_RenderPresent(renderer);
	static Uint64 prev = 0;
	const Uint64 now = SDL_GetTicks();
	frametime = ( prev - now ) / 1000.0f;
	prev = now;
}

void sdl_quit(void)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
