#include <SDL3/SDL.h>
#include "defs.h"

static SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
float frametime = 0.0f;
bool quit = false;
const bool* keys = NULL;

void sdl_init(void) {
	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer("Raycaster", WINDOW_W, WINDOW_H, 0, &window, &renderer);
	SDL_SetRenderVSync(renderer, 1);
	keys = SDL_GetKeyboardState(NULL);
}

void sdl_update(void) {
	SDL_Event event;
	while ( SDL_PollEvent(&event) ) {
		switch ( event.type ) {
			case SDL_EVENT_QUIT: quit = true; break;
			case SDL_EVENT_KEY_DOWN: if ( event.key.key == SDLK_ESCAPE ) quit = true; break;
		}
	}
}

void sdl_begin_draw(void) {
	SDL_SetRenderDrawColor(renderer, BLACK);
	SDL_RenderClear(renderer);
}

void sdl_end_draw(void) {
	SDL_RenderPresent(renderer);
	static Uint64 prev = 0;
	const Uint64 now = SDL_GetTicks();
	frametime = (now - prev) / 1000.0f;
	prev = now;
}

void sdl_quit(void) {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}