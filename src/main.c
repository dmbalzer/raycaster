#define RAYMATH_IMPLEMENTATION
#include "raymath.h"

/* Temporary for Wall Buffer Renderering */
#include <SDL3/SDL.h>
#include "defs.h"

extern SDL_Renderer* renderer;
Uint32 wall_buffer[SCREEN_W * SCREEN_H] = { 0 };
SDL_Texture* wall_buffer_texture = NULL;
extern bool ray_sides[SCREEN_W];
extern float wall_strip_heights[SCREEN_W];

void wall_buffer_init(void) {
	wall_buffer_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_W, SCREEN_H);
	SDL_SetTextureScaleMode(wall_buffer_texture, SDL_SCALEMODE_NEAREST);
	for ( int i = 0; i < SCREEN_W * SCREEN_H; i++ ) wall_buffer[i] = 0xA0A0A0F0;
	SDL_UpdateTexture(wall_buffer_texture, NULL, wall_buffer, 4 * SCREEN_W);
}

void wall_buffer_update(void) {
	for ( int i = 0; i < SCREEN_W * SCREEN_H / 2; i++ ) wall_buffer[i] = 0x888888FF;
	for ( int i = SCREEN_W * SCREEN_H / 2; i < SCREEN_W * SCREEN_H - 1; i++ ) wall_buffer[i] = 0x404040FF;
	for ( int x = 0; x < SCREEN_W; x++ ) {
		
		for ( int y = 0; y < wall_strip_heights[x]; y++ ) {
			int offset = SCREEN_H / 2 - (wall_strip_heights[x] > SCREEN_H ? SCREEN_H : wall_strip_heights[x]) / 2;
			if ( y + offset >= SCREEN_H ) continue;
			wall_buffer[x + (y + offset) * SCREEN_W] = ray_sides[x] ? 0xF0F0F0FF : 0xF8F8F8FF;
		}
	}
	SDL_UpdateTexture(wall_buffer_texture, NULL, wall_buffer, 4 * SCREEN_W);
}

void wall_buffer_draw(void) {
	SDL_RenderTexture(renderer, wall_buffer_texture, NULL, NULL);
}

void wall_buffer_unload(void) {
	SDL_DestroyTexture(wall_buffer_texture);
}

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
