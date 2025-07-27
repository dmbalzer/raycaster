#include <stdbool.h>
#define RAYMATH_IMPLEMENTATION
#include "raymath.h"
#include "sdl.h"
#include "map.h"

bool quit = false;

int main(void)
{
	sdl_init();
	while ( !quit )
	{
		sdl_do_events();
		sdl_begin_draw();
		
		map_draw();

		sdl_end_draw();
	}

	sdl_quit();
	return 0;
}
