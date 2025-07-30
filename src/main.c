#define RAYMATH_IMPLEMENTATION
#include "raymath.h"
#include <stdbool.h>
#include "sdl.h"
#include "map.h"
#include "player.h"
#include "raycast.h"

extern bool quit;

int main(void)
{
	sdl_init();
	player_init();
	raycast_init();

	while ( !quit )
	{
		sdl_do_events();
		player_update();
		raycast_update();

		sdl_begin_draw();
		
		map_draw();
		player_draw();
		raycast_draw();

		sdl_end_draw();
	}

	sdl_quit();
	return 0;
}
