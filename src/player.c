#include "player.h"
#include "defs.h"
#include <SDL3/SDL.h>
#include "raymath.h"

extern SDL_Renderer* renderer;
extern float frametime;
extern const bool* keys;
extern const int map[];

Vector2 pos = { 0 };
Vector2 dir = { 0 };
Vector2 plane = { 0 };
static const float spd = 2.0f;

void player_init(void) {
	pos.x = 5.5f; pos.y = 5.5f;
	dir.x = 0.0f, dir.y = -1.0f;
	plane.x = 0.66f, plane.y = 0.0f;
}

void player_update(void) {
	bool up    = keys[SDL_SCANCODE_UP];
	bool down  = keys[SDL_SCANCODE_DOWN];
	bool right = keys[SDL_SCANCODE_RIGHT];
	bool left  = keys[SDL_SCANCODE_LEFT];

	dir = Vector2Rotate(dir, (right - left) * frametime);
	plane = Vector2Rotate(plane, (right - left) * frametime);

	Vector2 vel = Vector2Scale(dir, (up - down));
	vel = Vector2Normalize(vel);
	vel = Vector2Scale(dir, (up - down) * spd * frametime);
	/* Check x collision */
	if ( map[(int)(pos.x + vel.x) + (int)pos.y * MAP_W] != 0 ) vel.x = 0;
	/* Check y collision */
	if ( map[(int)pos.x + (int)(pos.y + vel.y) * MAP_W] != 0 ) vel.y = 0;

	pos = Vector2Add(pos, vel);
}

void player_draw(void) {
	SDL_SetRenderDrawColor(renderer, BLUE);
	SDL_FRect dst = (SDL_FRect){
		pos.x * TILE_SIZE - 4,
		pos.y * TILE_SIZE - 4,
		9, 9 };
	SDL_RenderFillRect(renderer, &dst);
}