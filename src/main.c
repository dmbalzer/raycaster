#include <stdbool.h>
#define RAYMATH_IMPLEMENTATION
#include "raymath.h"
#include "sdl.h"
#include "map.h"
#include "player.h"
#include "ray.h"

extern bool quit;

int main(void) {
	sdl_init();
	player_init();

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