#include <SDL3/SDL.h>
#include "defs.h"
#define RAYMATH_IMPLEMENTATION
#include "raymath.h"
#include "sdl.h"
#include "map.h"
#include "player.h"
#include "ray.h"

/* sdl.c */
extern SDL_Renderer* renderer;
extern float frametime;
extern float quit;
extern const bool* keys;

/* map.c */
extern const int map[];

/* player.c */
extern Vector2 pos;
extern Vector2 dir;
extern Vector2 plane;

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
