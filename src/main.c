#include <SDL3/SDL.h>
#include "sdl.h"
#define RAYMATH_IMPLEMENTATION
#include "raymath.h"

#define MAP_W 80
#define MAP_H 80
#define TILE_SIZE 8
#define MAP_PIXEL_W (MAP_W*TILE_SIZE)
#define MAP_PIXEL_H (MAP_H*TILE_SIZE)

#define SCREEN_W 240
#define SCREEN_H 240

#define FOV PI/2


extern SDL_Renderer* renderer;
extern float frametime;
bool quit = false;

Uint32 map_buffer[MAP_PIXEL_W * MAP_PIXEL_H] = { 0 };
SDL_Texture* map_texture = NULL;

Vector2 pos = { 0 };
Vector2 dir = { 0 };
Vector2 plane = { 0 };

int main(void)
{
	sdl_init();
	
	/* Init Map */
	map_texture = SDL_CreateTexture(
		renderer,
		SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_STREAMING,
		MAP_PIXEL_W,
		MAP_PIXEL_H);

	/* Clear map with BLACK */
	for ( int i = 0; i < MAP_PIXEL_W * MAP_PIXEL_H; i++ )
	{
		map_buffer[i] = BLACK_HEX;
	}
	
	/* Update map texture */
	SDL_UpdateTexture(map_texture, NULL, map_buffer, 4 * MAP_PIXEL_W);

	/* Init Player */
	pos.x = MAP_PIXEL_W / 2;
	pos.y = MAP_PIXEL_H / 2;
	dir.x = 0;
	dir.y = 1;

	while ( !quit )
	{
		sdl_do_events();

		dir = Vector2Rotate(dir, 1*frametime);
		plane = Vector2Rotate(dir, PI/2);

		sdl_begin_draw();
		
		/* Render Map */	
		SDL_FRect dst = (SDL_FRect){0, 0, map_texture->w, map_texture->h};
		SDL_RenderTexture(renderer, map_texture, NULL, &dst);
		
		/* Render Player */
		SDL_SetRenderDrawColor(renderer, GREEN);
		SDL_FRect position_rect = (SDL_FRect){pos.x - 4, pos.y - 4, 8, 8 };
		SDL_RenderFillRect(renderer, &position_rect);
		
		/* Render Direction Vector */
		{
			SDL_SetRenderDrawColor(renderer, BLUE);
			/* Get line end point from direction vector scaled by length to screen */
			Vector2 end = Vector2Add(pos, Vector2Scale(dir, SCREEN_W/2 / tan(PI/4)));
			SDL_RenderLine(renderer, pos.x, pos.y, end.x, end.y);
		}
		
		/* Render Plane Vector */
		{
			SDL_SetRenderDrawColor(renderer, GREEN);
			/* Get line direction end point from direction vector scaled by length to screen */
			Vector2 dir_end = Vector2Add(pos, Vector2Scale(dir, SCREEN_W/2 / tan(PI/4)));
			/* Move start point to left of screen */
			Vector2 start = Vector2Subtract(dir_end, Vector2Scale(plane, SCREEN_W/2));
			/* Get end point at left of screen */
			Vector2 end = Vector2Add(dir_end, Vector2Scale(plane, SCREEN_W/2));
			SDL_RenderLine(renderer, start.x, start.y, end.x, end.y);
		}

		sdl_end_draw();
	}
	
	SDL_DestroyTexture(map_texture);	

	sdl_quit();
	return 0;
}

/***********************************************
SDL_Texture* texture = NULL;

texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, 80, 80);


SDL_RenderTexture(renderer, texture, NULL, NULL);
SDL_DestroyTexture(texture);

*************************************************/
