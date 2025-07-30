#include "defs.h"
#include "map.h"
#include <SDL3/SDL.h>

extern SDL_Renderer* renderer;

const int map_data[] = {
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
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
};

void map_draw(void)
{
	SDL_SetRenderDrawColor(renderer, WHITE);
	for ( int y = 0; y < MAP_H; y++ )
	{
		for ( int x = 0; x < MAP_W; x++ )
		{
			if ( map_data[x + y * MAP_W] == 0 ) continue;

			SDL_FRect dst = (SDL_FRect){ x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE };
			SDL_RenderFillRect(renderer, &dst);
		}
	}

	SDL_SetRenderDrawColor(renderer, BLACK);
	for ( int y = 0; y < MAP_H; y++ )
	{
		for ( int x = 0; x < MAP_W; x++ )
		{
			SDL_RenderLine(renderer, 0, y * TILE_SIZE, MAP_W * TILE_SIZE, y * TILE_SIZE);
			SDL_RenderLine(renderer, x * TILE_SIZE, 0, x * TILE_SIZE, MAP_H * TILE_SIZE);
		}
	}
}
