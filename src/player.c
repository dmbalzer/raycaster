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
static Vector2 dir_end = { 0 };
static Vector2 plane = { 0 };
static Vector2 plane_start = { 0 };
static Vector2 plane_end = { 0 };

static float spd = 60.0f;

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
	plane = Vector2Rotate(plane, ( keys[SDL_SCANCODE_RIGHT] - keys[SDL_SCANCODE_LEFT] ) * frametime);

	/* Update direction and plane position vectors */
	dir_end = Vector2Add(pos, Vector2Scale(dir, 40));
	plane_start = Vector2Subtract(dir_end, Vector2Scale(plane, 40));
	plane_end = Vector2Add(dir_end, Vector2Scale(plane, 40));
	
	/* Move player in direction with up and down keys */
	Vector2 vel = Vector2Scale(dir, (keys[SDL_SCANCODE_UP] - keys[SDL_SCANCODE_DOWN]) * spd * frametime);
	
	/* Check x movement collission */
	{
		int map_x = (int)((pos.x + vel.x) / TILE_SIZE);
		int map_y = (int)(pos.y / TILE_SIZE);
		if ( !map_data[ map_x + map_y * MAP_W ] ) pos.x += vel.x;
	}
	/* Check y movement collission */
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
	SDL_RenderLine(renderer, pos.x, pos.y, dir_end.x, dir_end.y);

	/* Draw Scaled Plane Vector */
	SDL_SetRenderDrawColor(renderer, RED);
	SDL_RenderLine(renderer, plane_start.x, plane_start.y, plane_end.x, plane_end.y);
}
