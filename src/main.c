#define RAYMATH_IMPLEMENTATION
#include "raymath.h"
#include <stdbool.h>

#include "sdl.h"
#include "map.h"
#include "player.h"
#include "ray.h"
#include "wall.h"

extern bool quit;

int main(void) {
	sdl_init();
	player_init();
	wall_buffer_init();

	while ( !quit ) {
		sdl_update();
		player_update();
		ray_update();
		wall_buffer_update();

		sdl_begin_draw();

		map_draw();
		player_draw();
		ray_draw();
		wall_buffer_draw();


		sdl_end_draw();
	}

	wall_buffer_unload();
	sdl_quit();
	return 0;
}
