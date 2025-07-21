#ifndef SDL_INCLUDED
#define SDL_INCLUDED

#define SCREEN_W 320
#define SCREEN_H 240

#define WINDOW_W (SCREEN_W*4)
#define WINDOW_H (SCREEN_H*4)

void sdl_init(void);
void sdl_do_events(void);
void sdl_begin_draw(void);
void sdl_end_draw(void);
void sdl_quit(void);

#endif // SDL_INCLUDED
