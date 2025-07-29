#define RAYMATH_IMPLEMENTATION
#include "raymath.h"
#include <stdbool.h>
#include "sdl.h"
#include "map.h"
#include "player.h"

bool quit = false;
int dir_keys[4] = { 0 };

int main(void)
{
	sdl_init();
	player_init();

	while ( !quit )
	{
		sdl_do_events();
		player_update();

		sdl_begin_draw();
		
		map_draw();
		player_draw();

		sdl_end_draw();
	}

	sdl_quit();
	return 0;
}
