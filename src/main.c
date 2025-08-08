#define RAYMATH_IMPLEMENTATION
#include "raymath.h"

/* Temporary for Buffer */
#include <SDL3/SDL.h>
#include "defs.h"

extern SDL_Renderer* renderer;
Uint32 buffer[SCREEN_W * SCREEN_H] = { 0 };
SDL_Texture* buffer_texture = NULL;
extern bool ray_sides[SCREEN_W];
extern float perp_dists[SCREEN_W];
extern float wall_strip_heights[SCREEN_W];
/********************/
#include <stdbool.h>

#include "sdl.h"
#include "map.h"
#include "player.h"
#include "ray.h"

extern bool quit;

int main(void) {
	sdl_init();
	player_init();

	buffer_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_W, SCREEN_H);
	SDL_SetTextureScaleMode(buffer_texture, SDL_SCALEMODE_NEAREST);
	for ( int i = 0; i < SCREEN_W * SCREEN_H; i++ ) buffer[i] = 0xA0A0A0F0;
	SDL_UpdateTexture(buffer_texture, NULL, buffer, 4 * SCREEN_W);

	while ( !quit ) {
		sdl_update();
		player_update();
		ray_update();
		for ( int i = 0; i < SCREEN_W * SCREEN_H; i++ ) buffer[i] = 0xA0A0A0F0;
		for ( int x = 0; x < SCREEN_W; x++ ) {
			
			for ( int y = 0; y < wall_strip_heights[x]; y++ ) {
				int offset = SCREEN_H - (wall_strip_heights[2] / 2) > SCREEN_H ? SCREEN_H : (wall_strip_heights[2] / 2);
				if ( y + offset >= SCREEN_H ) continue;
				buffer[x + (y + offset) * SCREEN_W] = ray_sides[x] ? 0xFFFFFFFF : 0xE0E0E0FF;
			}
		}
		SDL_UpdateTexture(buffer_texture, NULL, buffer, 4 * SCREEN_W);
		sdl_begin_draw();

		map_draw();
		player_draw();
		ray_draw();

		SDL_RenderTexture(renderer, buffer_texture, NULL, NULL);

		sdl_end_draw();
	}

	sdl_quit();
	return 0;
}