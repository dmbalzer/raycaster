#include "defs.h"
#include "player.h"
#include <SDL3/SDL.h>
#include "raymath.h"

extern SDL_Renderer* renderer;
extern float frametime;

static Vector2 pos = { 0 };
static Vector2 dir = { 0 };
static const float screen_dist = SCREEN_W / 2 / tan(FOV / 2);

void player_init(void)
{
	pos.x = MAP_W * TILE_SIZE / 2;
	pos.y = MAP_H * TILE_SIZE / 2;
	
	dir.y = 1;	
}

void player_update(void)
{

}

void player_draw(void)
{
	/* Draw Player */
	SDL_SetRenderDrawColor(renderer, BLUE);
	SDL_FRect dst = (SDL_FRect){ pos.x, pos.y, 8, 8 };
	SDL_RenderFillRect(renderer, &dst);

	/* Draw Scaled Direction Vector */
	SDL_SetRenderDrawColor(renderer, GREEN);
	Vector2 dir_start = (Vector2){ pos.x + 4, pos.y + 4 };
	Vector2 dir_end   = Vector2Add(dir_start, Vector2Scale(dir, screen_dist));
	SDL_RenderLine(renderer, dir_start.x, dir_start.y, dir_end.x, dir_end.y);

	/* Draw Camera Vector */
	SDL_SetRenderDrawColor(renderer, RED);
	Vector2 cam = Vector2Rotate(dir, PI / 2);
	Vector2 cam_start = Vector2Subtract(dir_end, Vector2Scale(cam, SCREEN_W / 2));
	Vector2 cam_end = Vector2Add(cam_start, Vector2Scale(cam, SCREEN_W));
	SDL_RenderLine(renderer, cam_start.x, cam_start.y, cam_end.x, cam_end.y);
}
