#include "raycast.h"
#include "defs.h"
#include <SDL3/SDL.h>
#include "raymath.h"

extern SDL_Renderer* renderer;
extern Vector2 pos;
extern bool* keys;
extern float frametime;
extern const int map_data[];

Vector2 dir = { 0 };
Vector2 plane = { 0 };
Vector2 dir_end = { 0 };
Vector2 plane_start = { 0 };
Vector2 plane_end = { 0 };
static float fov = 0.0f;

void raycast_init(void)
{
	dir.x = 1.0f;	
	plane.y = 0.66f;
	fov = 2 * atan2f(0.66f, 1.0f);
}

void raycast_update(void)
{
    /* Rotate direction with right and left keys */
	dir = Vector2Rotate(dir, ( keys[SDL_SCANCODE_RIGHT] - keys[SDL_SCANCODE_LEFT] ) * frametime);
	plane = Vector2Rotate(plane, ( keys[SDL_SCANCODE_RIGHT] - keys[SDL_SCANCODE_LEFT] ) * frametime);
}

void raycast_draw(void)
{
	/* Draw Rays */
	SDL_SetRenderDrawColor(renderer, GREEN);
	for ( int i = 0; i < SCREEN_W; i++ )
	{
		float cam_x = 2 * (i / (float)SCREEN_W) - 1;
		
		Vector2 cam_dir = {
			.x = dir.x + plane.x * cam_x,
			.y = dir.y + plane.y * cam_x
		};
		Vector2 cam_end = Vector2Add(pos, Vector2Scale(cam_dir, 1000));
		SDL_RenderLine(renderer, pos.x, pos.y, cam_end.x, cam_end.y);
	}
}