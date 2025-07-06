#include <SDL3/SDL.h>

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* texture = NULL;
Uint32 buffer[80 * 80] = { 0 };
bool quit = false;

int main(void)
{
	if ( !SDL_Init(SDL_INIT_VIDEO) )
	{
		SDL_Log("%s", SDL_GetError());
		return -1;
	}

	if ( !SDL_CreateWindowAndRenderer("Raycaster", 960, 640, 0, &window, &renderer) )
	{
		SDL_Log("%s", SDL_GetError());
		return -1;
	}

	if ( !SDL_SetRenderVSync(renderer, 1) )
	{
		SDL_Log("%s", SDL_GetError());
		return -1;
	}
	
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, 80, 80);
	
	for ( int i = 0; i < 80 * 80; i++ )
	{
		buffer[i] = 0xFFF080FF;
	}
	
	SDL_UpdateTexture(texture, NULL, buffer, 4 * 80);

	while ( !quit )
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

		SDL_SetRenderDrawColor(renderer, 0xFF,0xFF,0xFF,0xFF);
		SDL_RenderClear(renderer);
		SDL_FRect dst = (SDL_FRect){ 0,0,80,80 };
		SDL_RenderTexture(renderer, texture, NULL, &dst);
		SDL_RenderPresent(renderer);
	}
	
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
