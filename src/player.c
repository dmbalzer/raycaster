#include "defs.h"
#include "player.h"
#include <SDL3/SDL.h>
#include "raymath.h"

extern SDL_Renderer* renderer;
extern float frametime;

static Vector2 pos = { 0 };

void player_init(void)
{
	pos.x = MAP_W * TILE_SIZE / 2;
	pos.y = MAP_H * TILE_SIZE / 2;
}

void player_update(void)
{

}

void player_draw(void)
{
	SDL_SetRenderDrawColor(renderer, BLUE);
	SDL_FRect dst = (SDL_FRect){ pos.x, pos.y, 9, 9 };
	SDL_RenderFillRect(renderer, &dst);
}
