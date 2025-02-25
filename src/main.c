#include "defs.h"
#include "sdl.h"
#include "map.h"
#include "player.h"

extern SDL_Renderer* renderer;

int main(void)
{
	sdl_init();
	bool quit = false;

	Player player = { 0 };
	player.x = 64.0f;
	player.y = 64.0f;
	player.rot_angle = PI/2.0f;
	player.speed = 60.0f;
	player.rot_speed = 60.0f*DEG2RAD;

	while ( !quit ) {
		sdl_process_events();
		if ( sdl_window_closed() ) quit = true;
		player_move(&player);
		sdl_begin_drawing();
		map_draw();
		player_draw(player);
		sdl_end_drawing();
	}
	sdl_unload();
	return 0;
}
