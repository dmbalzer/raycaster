#include <SDL3/SDL.h>

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* texture = NULL;
Uint32 buffer[80 * 80] = { 0 };
bool quit = false;

void sdl_init(void)
{
	if ( !SDL_Init(SDL_INIT_VIDEO) )
	{
		SDL_Log("%s", SDL_GetError());
		exit(-1);
	}

	if ( !SDL_CreateWindowAndRenderer("Raycaster", 960, 640, 0, &window, &renderer) )
	{
		SDL_Log("%s", SDL_GetError());
		exit(-1);
	}

	if ( !SDL_SetRenderVSync(renderer, 1) )
	{
		SDL_Log("%s", SDL_GetError());
		exit(-1);
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
	SDL_SetRenderDrawColor(renderer, 0xFF,0xFF,0xFF,0xFF);
	SDL_RenderClear(renderer);
}

void sdl_end_draw(void)
{
	SDL_RenderPresent(renderer);
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
