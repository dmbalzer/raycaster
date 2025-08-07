#include <SDL3/SDL.h>
#include "defs.h"
#define RAYMATH_IMPLEMENTATION
#include "raymath.h"
#include "sdl.h"

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

extern SDL_Renderer* renderer;
extern float frametime;
extern float quit;
extern const bool* keys;

static Vector2 pos = { 0 };
static Vector2 dir = { 0 };
static Vector2 plane = { 0 };
static const float spd = 2.0f;

static void player_init(void) {
	pos.x = 5.5f; pos.y = 5.5f;
	dir.x = 0.0f, dir.y = -1.0f;
	plane.x = 0.66f, plane.y = 0.0f;
}

static void player_update(void) {
	bool up    = keys[SDL_SCANCODE_UP];
	bool down  = keys[SDL_SCANCODE_DOWN];
	bool right = keys[SDL_SCANCODE_RIGHT];
	bool left  = keys[SDL_SCANCODE_LEFT];

	dir = Vector2Rotate(dir, (right - left) * frametime);
	plane = Vector2Rotate(plane, (right - left) * frametime);

	Vector2 vel = Vector2Scale(dir, (up - down));
	vel = Vector2Normalize(vel);
	vel = Vector2Scale(dir, (up - down) * spd * frametime);
	/* Check x collision */
	if ( map[(int)(pos.x + vel.x) + (int)pos.y * MAP_W] != 0 ) vel.x = 0;
	/* Check y collision */
	if ( map[(int)pos.x + (int)(pos.y + vel.y) * MAP_W] != 0 ) vel.y = 0;

	pos = Vector2Add(pos, vel);
}

static void player_draw(void) {
	for ( int i = 0; i < SCREEN_W; i++ ) {
		float x = 2 * i / (float)SCREEN_W - 1;
		Vector2 ray_dir = (Vector2){
			.x = dir.x + plane.x * x,
			.y = dir.y + plane.y * x
		};

		/******************************************************
		 * Horizontal Side Checks
		 ******************************************************/
		/* Horizontal Side Vector*/
		Vector2 hside = { 0 };
		hside.y = ray_dir.y < 0 ? (int)pos.y - pos.y : (int)pos.y - pos.y + 1;
		hside.x = hside.y / tan(Vector2Angle((Vector2){1.0f, 0.0f}, ray_dir));

		/* Horizontal Step Vector*/
		Vector2 hstep = { 0 };
		hstep.y = ray_dir.y < 0 ? -1 : 1;
		hstep.x = hstep.y / tan(Vector2Angle((Vector2){1.0f, 0.0f}, ray_dir));

		bool hit = false;
		Vector2 hray = hside;
		while ( !hit ) {
			int x = (int)(pos.x + hray.x);
			if ( x >= MAP_W ) x = MAP_W - 1;
			if ( x < 0 ) x = 0;
			int y = ray_dir.y < 0 ? (int)(pos.y + hray.y) - 1 : (int)(pos.y + hray.y);
			if ( y >= MAP_H ) y = MAP_H - 1;
			if ( y < 0 ) y = 0;
			if ( map[ x + y * MAP_W ] != 0 ) {
				
				break;
			}
			hray = Vector2Add(hray, hstep);
		}

		/******************************************************
		 * Vertical Side Checks
		 ******************************************************/
		/* Vertical Side Vector*/
		Vector2 vside = { 0 };

		vside.x = ray_dir.x < 0 ? (int)pos.x - pos.x : (int)pos.x - pos.x + 1;
		vside.y = vside.x * tan(Vector2Angle((Vector2){1.0f, 0.0f}, ray_dir));

		/* Vertical Step Vector*/
		Vector2 vstep = { 0 };
		vstep.x = ray_dir.x < 0 ? -1 : 1;
		vstep.y = vstep.x * tan(Vector2Angle((Vector2){1.0f, 0.0f}, ray_dir));

		hit = false;
		Vector2 vray = vside;
		while ( !hit ) {
			int x = ray_dir.x < 0 ? (int)(pos.x + vray.x) - 1: (int)(pos.x + vray.x);
			if ( x >= MAP_W ) x = MAP_W - 1;
			if ( x < 0 ) x = 0;
			int y = (int)(pos.y + vray.y);
			if ( y >= MAP_H ) y = MAP_H - 1;
			if ( y < 0 ) y = 0;
			if ( map[ x + y * MAP_W ] != 0 ) {
				
				break;
			}
			vray = Vector2Add(vray, vstep);
		}
		
		Vector2 ray = (Vector2Length(hray) < Vector2Length(vray)) ? hray : vray;

		/* Draw Ray */
		SDL_SetRenderDrawColor(renderer, GREEN);
		SDL_RenderLine(renderer,
			pos.x * TILE_SIZE,
			pos.y * TILE_SIZE,
			(pos.x + ray.x) * TILE_SIZE,
			(pos.y + ray.y) * TILE_SIZE);
	}

	SDL_SetRenderDrawColor(renderer, BLUE);
	SDL_FRect dst = (SDL_FRect){
		pos.x * TILE_SIZE - 4,
		pos.y * TILE_SIZE - 4,
		9, 9 };
	SDL_RenderFillRect(renderer, &dst);
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

	while ( !quit ) {
		sdl_update();
		player_update();

		sdl_begin_draw();

		map_draw();
		player_draw();

		sdl_end_draw();
	}

	sdl_quit();
	return 0;
}
