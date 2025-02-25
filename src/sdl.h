#ifndef SDL_INCLUDED
#define SDL_INCLUDED

#include <SDL3/SDL.h>

void sdl_init(void);
void sdl_process_events(void);
bool sdl_window_closed(void);
void sdl_begin_drawing(void);
void sdl_end_drawing(void);
void sdl_unload(void);

#endif // SDL_INCLUDED
