#include <SDL3/SDL.h>
#include "sdl.h"

extern SDL_Renderer* renderer;
bool quit = false;

Uint32 buffer[80 * 80] = { 0 };
SDL_Texture* texture = NULL;

int main(void)
{
	sdl_init();
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, 80, 80);
	
	for ( int i = 0; i < 80 * 80; i++ )
	{
		buffer[i] = 0x5FCDE4FF;
	}
	
	SDL_UpdateTexture(texture, NULL, buffer, 4 * 80);

	while ( !quit )
	{

		sdl_do_events();
		sdl_begin_draw();
		SDL_RenderTexture(renderer, texture, NULL, NULL);
		sdl_end_draw();
	}
	
	SDL_DestroyTexture(texture);
	sdl_quit();
	return 0;
}
