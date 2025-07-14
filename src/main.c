#include <SDL3/SDL.h>
#include "sdl.h"

#define MAP_W 256
#define MAP_H 256

extern SDL_Renderer* renderer;
bool quit = false;

Uint32 map_buffer[MAP_W * MAP_H] = { 0 };
SDL_Texture* map_texture = NULL;

typedef SDL_FPoint Vector;

Vector position = { 0 };

int main(void)
{
	sdl_init();
	
	/* Init Map */
	map_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, MAP_W, MAP_H);
	for ( int i = 0; i < MAP_W * MAP_H; i++ )
	{
		map_buffer[i] = 0x000000FF;
	}
	SDL_UpdateTexture(map_texture, NULL, map_buffer, 4 * MAP_W);

	/* Init Player */
	position.x = MAP_W / 2;
	position.y = MAP_H / 2;

	while ( !quit )
	{

		sdl_do_events();
		sdl_begin_draw();
		
		/* Render Map */	
		SDL_FRect dst = (SDL_FRect){0, 0, map_texture->w, map_texture->h};
		SDL_RenderTexture(renderer, map_texture, NULL, &dst);
		
		/* Render Player */
		SDL_SetRenderDrawColor(renderer, GREEN);
		SDL_FRect position_rect = (SDL_FRect){position.x - 4, position.y - 4, 8, 8 };
		SDL_RenderFillRect(renderer, &position_rect);

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
