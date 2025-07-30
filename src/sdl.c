#include "defs.h"
#include "sdl.h"
#include <SDL3/SDL.h>

static SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
bool quit = false;
float frametime = 0.0f;

const bool* keys;

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

	keys = SDL_GetKeyboardState(NULL);

	if ( keys == NULL )
	{
		SDL_Log("%s", SDL_GetError()); exit(-1);
	}
}

void sdl_do_events(void)
{
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
