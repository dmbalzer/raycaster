#include "defs.h"
#include "player.h"
#include <SDL3/SDL.h>
#include <stdio.h>

extern SDL_Renderer* renderer;
extern float frametime;
extern bool* keystate;

void player_move(Player* player)
{
	int front = keystate[SDL_SCANCODE_W] ?  1 : 0;
	int left =  keystate[SDL_SCANCODE_A] ? -1 : 0;
	int back =  keystate[SDL_SCANCODE_S] ? -1 : 0;
	int right = keystate[SDL_SCANCODE_D] ?  1 : 0;
	player->turn_dir = right + left;
	player->walk_dir = front + back;
	player->x += player->walk_dir*player->speed*frametime;
}

void player_draw(Player player)
{
	SDL_SetRenderDrawColor(renderer, RED);
	SDL_FRect rec = (SDL_FRect){ player.x-4.0f, player.y-4.0f, 9.0f, 9.0f };
	SDL_RenderFillRect(renderer, &rec);
}
