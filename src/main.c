#include <SDL3/SDL.h>
#define RAYMATH_IMPLEMENTATION
#include "raymath.h"

#define BLACK   0x00,0x00,0x00,0xFF
#define WHITE   0xFF,0xFF,0xFF,0xFF
#define RED     0xFF,0x00,0x00,0xFF
#define GREEN   0x00,0xFF,0x00,0xFF
#define BLUE    0x00,0x00,0xFF,0xFF
#define YELLOW  0xFF,0xFF,0x00,0xFF
#define ORANGE  0xFF,0xA5,0x00,0xFF
#define MAGENTA 0xFF,0x00,0xFF,0xFF

#define WINDOW_W 960
#define WINDOW_H 640
#define SCREEN_W 240
#define SCREEN_H 160

#define MAP_W 15
#define MAP_H 11
#define TILE_SIZE 24

static const int map[] = {
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

static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;
static float frametime = 0.0f;
static bool quit = false;
static const bool* keys = NULL;

static void sdl_init(void) {
	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer("Raycaster", WINDOW_W, WINDOW_H, 0, &window, &renderer);
	SDL_SetRenderVSync(renderer, 1);
	keys = SDL_GetKeyboardState(NULL);
}

static void sdl_update(void) {
	SDL_Event event;
	while ( SDL_PollEvent(&event) ) {
		switch ( event.type ) {
			case SDL_EVENT_QUIT: quit = true; break;
			case SDL_EVENT_KEY_DOWN: if ( event.key.key == SDLK_ESCAPE ) quit = true; break;
		}
	}
}

static void sdl_begin_draw(void) {
	SDL_SetRenderDrawColor(renderer, BLACK);
	SDL_RenderClear(renderer);
}

static void sdl_end_draw(void) {
	SDL_RenderPresent(renderer);
	static Uint64 prev = 0;
	const Uint64 now = SDL_GetTicks();
	frametime = (now - prev) / 1000.0f;
	prev = now;
}

static void sdl_quit(void) {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

static Vector2 pos = { 0 };
static Vector2 dir = { 0 };
static Vector2 plane = { 0 };
static const float spd = 8.0f;

static void player_init(void) {
	pos.x = 10.0f; pos.y = 10.0f;
}

static void player_update(void) {
	bool up    = keys[SDL_SCANCODE_UP];
	bool down  = keys[SDL_SCANCODE_DOWN];
	pos = Vector2Add(pos, Vector2Scale(dir, (up - down) * spd * frametime));
}

static void player_draw(void) {
	SDL_SetRenderDrawColor(renderer, BLUE);
	SDL_FRect dst = (SDL_FRect){
		pos.x * TILE_SIZE - 4,
		pos.y * TILE_SIZE - 4,
		9, 9 };
	SDL_RenderFillRect(renderer, &dst);
}

static void ray_init(void) {
	dir.x = 1.0f;
	plane.y = 0.66f;
}

static void ray_update(void) {
	bool left  = keys[SDL_SCANCODE_LEFT];
	bool right = keys[SDL_SCANCODE_RIGHT];
	
	dir = Vector2Rotate(dir, (right - left) * frametime);
	plane = Vector2Rotate(plane, (right - left) * frametime);
}

static void ray_draw(void) {
	SDL_SetRenderDrawColor(renderer, ORANGE);
	for ( int i = 0; i < SCREEN_W; i++ ) {
		float cam_x = 2 * i / (float)SCREEN_W - 1;
		Vector2 ray_dir = Vector2Add(Vector2Scale(plane, cam_x), dir);
		SDL_RenderLine(renderer,
			pos.x * TILE_SIZE,
			pos.y * TILE_SIZE,
			pos.x * TILE_SIZE + ray_dir.x * 100,
			pos.y * TILE_SIZE + ray_dir.y * 100);
	}
	
	SDL_SetRenderDrawColor(renderer, BLUE);
	SDL_RenderLine(renderer,
		pos.x * TILE_SIZE,
		pos.y * TILE_SIZE,
		pos.x * TILE_SIZE + dir.x * 100,
		pos.y * TILE_SIZE + dir.y * 100);
}

int main(void) {
	sdl_init();
	player_init();
	ray_init();
	
	while ( !quit ) {
		sdl_update();
		player_update();
		ray_update();
		
		sdl_begin_draw();
		
		player_draw();
		ray_draw();

		sdl_end_draw();
	}
	
	sdl_quit();
	return 0;
}
