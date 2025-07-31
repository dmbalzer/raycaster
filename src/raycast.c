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

	/* Update direction and plane position vectors */
	dir_end = Vector2Add(pos, Vector2Scale(dir, 40));
	plane_start = Vector2Subtract(dir_end, Vector2Scale(plane, 40));
	plane_end = Vector2Add(dir_end, Vector2Scale(plane, 40));
}

void raycast_draw(void)
{
	/* Draw Scaled Direction Vector */
	SDL_SetRenderDrawColor(renderer, GREEN);
	SDL_RenderLine(renderer, pos.x, pos.y, dir_end.x, dir_end.y);
	
	/* Draw Scaled Plane Vector */
	SDL_SetRenderDrawColor(renderer, RED);
	SDL_RenderLine(renderer, plane_start.x, plane_start.y, plane_end.x, plane_end.y);
	
	/* Draw Rays */
	SDL_SetRenderDrawColor(renderer, BLUE);
	Vector2 cam = dir_end;
	for ( int i = 0; i < 10; i++ )
	{
		SDL_RenderLine(renderer, pos.x, pos.y, cam.x, cam.y);
		cam = Vector2Add(cam, Vector2Scale(plane, 1/10));
	}
}