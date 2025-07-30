#include "defs.h"
#include "player.h"
#include <SDL3/SDL.h>
#include "raymath.h"

extern SDL_Renderer* renderer;
extern float frametime;
extern bool* keys;
extern const int map_data[];
extern Vector2 dir;
extern Vector2 dir_end;
extern Vector2 plane_start;
extern Vector2 plane_end;

Vector2 pos = { 0 };

static float spd = 60.0f;

void player_init(void)
{
	pos.x = MAP_W * TILE_SIZE / 2;
	pos.y = MAP_H * TILE_SIZE / 2;
}

void player_update(void)
{	
	/* Calculate player velocity in direction with up and down keys */
	Vector2 vel = Vector2Scale(dir, (keys[SDL_SCANCODE_UP] - keys[SDL_SCANCODE_DOWN]) * spd * frametime);
	
	/* Check x movement collision */
	{
		int map_x = (int)((pos.x + vel.x) / TILE_SIZE);
		int map_y = (int)(pos.y / TILE_SIZE);
		if ( !map_data[ map_x + map_y * MAP_W ] ) pos.x += vel.x;
	}
	/* Check y movement collision */
	{
		int map_x = (int)(pos.x / TILE_SIZE);
		int map_y = (int)((pos.y + vel.y) / TILE_SIZE);
		if ( !map_data[ map_x + map_y * MAP_W ] ) pos.y += vel.y;
	}
}

void player_draw(void)
{
	/* Draw Player */
	SDL_SetRenderDrawColor(renderer, BLUE);
	SDL_FRect dst = (SDL_FRect){ pos.x - 4, pos.y - 4, 9, 9 };
	SDL_RenderFillRect(renderer, &dst);
}
