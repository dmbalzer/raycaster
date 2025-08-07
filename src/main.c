#include <SDL3/SDL.h>
#include "defs.h"
#define RAYMATH_IMPLEMENTATION
#include "raymath.h"
#include "sdl.h"
#include "map.h"
#include "player.h"

extern SDL_Renderer* renderer;
extern float frametime;
extern float quit;
extern const bool* keys;
extern const int map[];

extern Vector2 pos;
extern Vector2 dir;
extern Vector2 plane;

void ray_draw(void) {
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
		ray_draw();

		sdl_end_draw();
	}

	sdl_quit();
	return 0;
}
