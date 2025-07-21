#include <SDL3/SDL.h>
#define RAYMATH_IMPLEMENTATION
#include "raymath.h"

#define SCREEN_W 320
#define SCREEN_H 240

#define WINDOW_W (SCREEN_W*4)
#define WINDOW_H (SCREEN_H*4)

#define MAP_W 15
#define MAP_H 11
#define TILE_SIZE 32
static const int map[MAP_W * MAP_H] = {
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
	1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1,
	1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
};

static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;
static float frametime = 0.0f;
static bool quit = false;

void sdl_init(void);
void sdl_do_events(void);
void sdl_begin_draw(void);
void sdl_end_draw(void);
void sdl_quit(void);

void map_draw(void)
{
	SDL_SetRenderDrawColor(renderer, 0xFF,0xFF,0xFF,0xFF);
	for ( int x = 0; x < MAP_W; x++ )
	{
		for ( int y = 0; y < MAP_H; y++ )
		{
			if ( map[ x + y * MAP_W ] == 0 )
			{
				continue;
			}
			SDL_FRect dst = (SDL_FRect){ x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE };
			SDL_RenderFillRect(renderer, &dst);
		}
	}
	SDL_SetRenderDrawColor(renderer, 0x0F,0x0F,0x0F,0xFF);
	for ( int x = 0; x < MAP_W; x++ )
	{
		for ( int y = 0; y < MAP_H; y++ )
		{
			SDL_RenderLine(renderer, x * TILE_SIZE, 0, x * TILE_SIZE, MAP_H * TILE_SIZE);
			SDL_RenderLine(renderer, 0, y * TILE_SIZE, MAP_W * TILE_SIZE, y * TILE_SIZE);
		}
	}
}

int main(void)
{
	sdl_init();
	
	while ( !quit )
	{
		sdl_do_events();

		sdl_begin_draw();

		map_draw();

		sdl_end_draw();
	}
	
	sdl_quit();
	return 0;
}

void sdl_init(void)
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer("Raycaster", WINDOW_W, WINDOW_H, 0, &window, &renderer);
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

