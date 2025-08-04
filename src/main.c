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
#define GRAY    0x50,0x50,0x50,0xFF

#define WINDOW_W 960
#define WINDOW_H 640
#define SCREEN_W 240
#define SCREEN_H 160

#define MAP_W 15
#define MAP_H 11
#define TILE_SIZE 32

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

static Vector2 pos = { 0 };
static Vector2 dir = { 0 };
static Vector2 plane = { 0 };
static const float spd = 2.0f;

static void sdl_init(void);
static void sdl_update(void);
static void sdl_begin_draw(void);
static void sdl_end_draw(void);
static void sdl_quit(void);

static void player_init(void) {
	pos.x = 5.5f; pos.y = 5.5f;
}

static void player_update(void) {
	bool up    = keys[SDL_SCANCODE_UP];
	bool down  = keys[SDL_SCANCODE_DOWN];

	Vector2 vel = Vector2Scale(dir, (up - down) * spd * frametime);
	/* Check x collision */
	if ( map[(int)(pos.x + vel.x) + (int)pos.y * MAP_W] != 0 ) vel.x = 0;
	/* Check y collision */
	if ( map[(int)pos.x + (int)(pos.y + vel.y) * MAP_W] != 0 ) vel.y = 0;

	pos = Vector2Add(pos, vel);
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
	SDL_SetRenderDrawColor(renderer, GREEN);
	for ( int i = 0; i < SCREEN_W; i++ ) {
		float x = 2 * i / (float)SCREEN_W - 1;
		Vector2 rd = Vector2Add(Vector2Scale(plane, x), dir);
		SDL_RenderLine(renderer, 
			pos.x * TILE_SIZE,
			pos.y * TILE_SIZE,
			(pos.x + rd.x) * TILE_SIZE,
			(pos.y + rd.y) * TILE_SIZE);
	}
}

static void map_draw(void) {
	SDL_SetRenderDrawColor(renderer, WHITE);
	for ( int x = 0; x < MAP_W; x++ ) {
		for ( int y = 0; y < MAP_H; y++ ) {
			if ( map[ x + y * MAP_W ] == 0 ) continue;
			SDL_FRect dst = (SDL_FRect){
				x * TILE_SIZE,
				y * TILE_SIZE,
				TILE_SIZE,
				TILE_SIZE};
			SDL_RenderFillRect(renderer, &dst);
		}
	}
	SDL_SetRenderDrawColor(renderer, GRAY);
	for ( int x = 0; x < MAP_W; x++ ) {
		for ( int y = 0; y < MAP_H; y++ ) {
			SDL_RenderLine(renderer,
				x * TILE_SIZE,
				0,
				x * TILE_SIZE,
				MAP_H * TILE_SIZE);
			SDL_RenderLine(renderer,
				0,
				y * TILE_SIZE,
				MAP_W * TILE_SIZE,
				y * TILE_SIZE);
		}
	}
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
		
		map_draw();
		player_draw();
		ray_draw();

		sdl_end_draw();
	}
	
	sdl_quit();
	return 0;
}

/*************************************************
 * SDL
 *************************************************/
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
