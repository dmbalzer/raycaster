#include "defs.h"
#include "sdl.h"
#include <SDL3/SDL.h>

static SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
extern bool quit;
float frametime = 0.0f;

extern int dir_keys[4];

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
	for ( int i = 0; i < 4; i++ ) dir_keys[i] = 0;

	SDL_Event event;
	while ( SDL_PollEvent(&event) )
	{
		switch ( event.type )
		{
			case SDL_EVENT_QUIT:
				quit = true;
			break;
			case SDL_EVENT_KEY_DOWN:
				switch ( event.key.key )
				{
					case SDLK_ESCAPE: quit = true; break;
					case SDLK_LEFT: dir_keys[LEFT] = 1; break;
					case SDLK_RIGHT: dir_keys[RIGHT] = 1; break;
					case SDLK_UP: dir_keys[UP] = 1; break;
					case SDLK_DOWN: dir_keys[DOWN] = 1; break;
				}
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
	frametime = ( now - prev ) / 1000.0f;
	prev = now;
}

void sdl_quit(void)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
