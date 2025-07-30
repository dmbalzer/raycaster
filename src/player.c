#include "defs.h"
#include "player.h"
#include <SDL3/SDL.h>
#include "raymath.h"

extern SDL_Renderer* renderer;
extern float frametime;
extern int dir_keys[4];

static Vector2 pos = { 0 };
static Vector2 dir = { 0 };
static const float screen_dist = SCREEN_W / 2 / tan(FOV / 2);

void player_init(void)
{
	pos.x = MAP_W * TILE_SIZE / 2;
	pos.y = MAP_H * TILE_SIZE / 2;
	
	dir.y = 1;	
	dir = Vector2Scale(dir, screen_dist);
}

void player_update(void)
{
	dir = Vector2Rotate(dir, 1 * frametime);
}

void player_draw(void)
{
	/* Draw Player */
	SDL_SetRenderDrawColor(renderer, BLUE);
	SDL_FRect dst = (SDL_FRect){ pos.x, pos.y, 8, 8 };
	SDL_RenderFillRect(renderer, &dst);

	/* Draw Scaled Direction Vector */
	SDL_SetRenderDrawColor(renderer, GREEN);
	Vector2 start = (Vector2){ pos.x, pos.y };
	Vector2 end = Vector2Add(start, dir);
	SDL_RenderLine(renderer, start.x, start.y, end.x, end.y);


}
