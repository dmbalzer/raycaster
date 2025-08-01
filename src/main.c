#include <SDL3/SDL.h>
#include <math.h>

#define BLACK  0x00,0x00,0x00,0xFF
#define WHITE  0xFF,0xFF,0xFF,0xFF
#define RED    0xFF,0x00,0x00,0xFF
#define GREEN  0x00,0xFF,0x00,0xFF
#define BLUE   0x00,0x00,0xFF,0xFF

#define WINDOW_W 960
#define WINDOW_H 640
#define SCREEN_W 240
#define SCREEN_H 160
#define TILE_SIZE 24

typedef SDL_FPoint Vector;

Vector VectorRotate(Vector v, float a) {
	Vector r = { 0 };
	float cosr = cosf(a);
	float sinr = sinf(a);
	r.x = v.x*cosr - v.y*sinr;
	r.y = v.x*sinr + v.y*cosr;
	return r;
}

Vector VectorAdd(Vector v1, Vector v2) {
	Vector r = { 0 };
	r.x = v1.x + v2.x;
	r.y = v1.y + v2.y;
	return r;
}

Vector VectorScale(Vector v, float s) {
	Vector r = { 0 };
	r.x = v.x * s;
	r.y = v.y * s;
	return r;
}

static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;
static float frametime = 0.0f;
static bool quit = false;
static const bool* keys = NULL;
static Vector pos = { 0 };
static Vector dir = { 0 };
static Vector pln = { 0 };

int main(void) {
	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer("Raycaster", WINDOW_W, WINDOW_H, 0, &window, &renderer);
	SDL_SetRenderVSync(renderer, 1);
	keys = SDL_GetKeyboardState(NULL);
	
	pos.x = 10.0f; pos.y = 10.0f;
	dir.x = 1.0f;
	pln.y = 0.66f;

	while ( !quit ) {
		SDL_Event event;
		while ( SDL_PollEvent(&event) ) {
			switch ( event.type ) {
				case SDL_EVENT_QUIT: quit = true; break;
				case SDL_EVENT_KEY_DOWN: if ( event.key.key == SDLK_ESCAPE ) quit = true; break;
			}
		}

		bool left  = keys[SDL_SCANCODE_LEFT];
		bool right = keys[SDL_SCANCODE_RIGHT];
		bool up    = keys[SDL_SCANCODE_UP];
		bool down  = keys[SDL_SCANCODE_DOWN];

		dir = VectorRotate(dir, (right - left) * frametime);
		pln = VectorRotate(pln, (right - left) * frametime);

		SDL_SetRenderDrawColor(renderer, BLACK);
		SDL_RenderClear(renderer);
		
		SDL_SetRenderDrawColor(renderer, BLUE);
		SDL_FRect dst = (SDL_FRect){ pos.x * TILE_SIZE - 2, pos.y * TILE_SIZE - 2, 5, 5 };
		SDL_RenderFillRect(renderer, &dst);
		
		SDL_SetRenderDrawColor(renderer, RED);
		Vector dir_end = VectorAdd(VectorScale(pos, TILE_SIZE), VectorScale(dir, 80));
		SDL_RenderLine(renderer, pos.x * TILE_SIZE, pos.y * TILE_SIZE, dir_end.x, dir_end.y);

		SDL_RenderPresent(renderer);
		static Uint64 prev = 0;
		const Uint64 now = SDL_GetTicks();
		frametime = (now - prev) / 1000.0f;
		prev = now;
	}
	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
