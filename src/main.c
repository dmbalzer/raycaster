#include <SDL3/SDL.h>
#define RAYMATH_IMPLEMENTATION
#include "raymath.h"

static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;
static float frametime = 0.0f;
static bool quit = false;

void sdl_init(void)
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer("Raycaster", 960, 640, 0, &window, &renderer);
	SDL_SetRenderVSync(renderer, 1);
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
				if ( event.key.key == SDLK_ESCAPE )
				{
					quit = true;
				}
			break;
		}
	}
}

void sdl_begin_draw(void)
{
	SDL_SetRenderDrawColor(renderer, 0x00,0x00,0x00,0xFF);
	SDL_RenderClear(renderer);
}

void sdl_end_draw(void)
{
	SDL_RenderPresent(renderer);
	static Uint64 prev = 0;
	const Uint64 now = SDL_GetTicks();
	frametime = ( prev - now ) /1000.0f;
	prev = now;
}

void sdl_quit(void)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

int main(void)
{
	sdl_init();
	
	while ( !quit )
	{
		sdl_do_events();

		sdl_begin_draw();

		sdl_end_draw();
	}
	
	sdl_quit();
	return 0;
}
