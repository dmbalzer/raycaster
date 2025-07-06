#include <SDL3/SDL.h>

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
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
			}
		}

		SDL_SetRenderDrawColor(renderer, 0x00,0x00,0x00,0xFF);
		SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);
	}
	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
