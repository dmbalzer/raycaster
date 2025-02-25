#include "map.h"
#include "defs.h"
#include <SDL3/SDL.h>

extern SDL_Renderer* renderer;

static const int map[MAP_W*MAP_H] = {
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,1,0,1,
	1,0,0,1,1,1,1,0,0,0,0,0,0,0,1,
	1,0,0,1,0,0,1,0,0,0,0,0,1,0,1,
	1,0,0,1,0,0,1,0,0,0,0,0,0,0,1,
	1,0,0,1,0,0,1,0,0,0,0,0,1,0,1,
	1,0,0,0,0,0,0,1,1,0,0,0,0,0,1,
	1,0,0,0,0,0,0,1,1,0,0,0,1,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
};

void map_draw(void)
{
	SDL_SetRenderDrawColor(renderer, WHITE);
	for ( int y = 0; y < MAP_H; y++ ) {
		for ( int x = 0; x < MAP_W; x++ ) {
			int tile = map[x + y * MAP_W];
			if ( tile == 0 ) continue;
			SDL_FRect rec =	(SDL_FRect){ x*TILE_SIZE,y*TILE_SIZE,TILE_SIZE,TILE_SIZE };
			SDL_RenderFillRect(renderer, &rec);
		}
	}
	SDL_SetRenderDrawColor(renderer, GRAY);
	for ( int y = 0; y < MAP_H; y++ ) {
		for ( int x = 0; x < MAP_W; x++ ) {
			SDL_RenderLine(renderer, x*TILE_SIZE, 0, x*TILE_SIZE, MAP_H*TILE_SIZE);
			SDL_RenderLine(renderer, 0, y*TILE_SIZE,  MAP_W*TILE_SIZE, y*TILE_SIZE);
		}
	}
}
