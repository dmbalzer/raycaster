#include "defs.h"
#include "player.h"
#include <SDL3/SDL.h>
#include "raymath.h"

extern SDL_Renderer* renderer;
extern float frametime;
extern bool* keys;
extern const int map_data[];


static Vector2 pos = { 0 };
static Vector2 dir = { 0 };
static Vector2 plane = { 0 };
static const float spd = 60.0f;

void player_init(void)
{
	pos.x = MAP_W * TILE_SIZE / 2;
	pos.y = MAP_H * TILE_SIZE / 2;
	
	dir.x = 1;	
	plane.y = 0.66;
}

void player_update(void)
{
	/* Rotate direction with right and left keys */
	dir = Vector2Rotate(dir, ( keys[SDL_SCANCODE_RIGHT] - keys[SDL_SCANCODE_LEFT] ) * frametime);

	/* Move player in direction with up and down keys */
	Vector2 vel = Vector2Scale(dir, (keys[SDL_SCANCODE_UP] - keys[SDL_SCANCODE_DOWN]) * spd * frametime);
	{
		int map_x = (int)((pos.x + vel.x) / TILE_SIZE);
		int map_y = (int)(pos.y / TILE_SIZE);
		if ( !map_data[ map_x + map_y * MAP_W ] ) pos.x += vel.x;
	}
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

	/* Draw Scaled Direction Vector */
	SDL_SetRenderDrawColor(renderer, GREEN);
	Vector2 end = Vector2Add(pos, Vector2Scale(dir, 40));
	SDL_RenderLine(renderer, pos.x, pos.y, end.x, end.y);


}
