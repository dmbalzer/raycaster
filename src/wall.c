#include "wall.h"
#include <SDL3/SDL.h>
#include "defs.h"

extern SDL_Renderer* renderer;
Uint32 wall_buffer[SCREEN_W * SCREEN_H] = { 0 };
SDL_Texture* wall_buffer_texture = NULL;
extern bool ray_sides[SCREEN_W];
extern float wall_strip_heights[SCREEN_W];
extern int map_hit_nos[SCREEN_W];

const Uint32 map_colors[] = {
    0x000000FF,
    0xFF0000FF,
    0x00FF00FF,
    0x0000FFFF
};

const Uint32 map_colors_darker[] = {
    0x000000FF,
    0xAA0000FF,
    0x00AA00FF,
    0x0000AAFF
};

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
			// wall_buffer[x + (y + offset) * SCREEN_W] = ray_sides[x] ? 0xF0F0F0FF : 0xF8F8F8FF;
			wall_buffer[x + (y + offset) * SCREEN_W] = ray_sides[x] ? map_colors[map_hit_nos[x]] : map_colors_darker[map_hit_nos[x]];
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