#ifndef SDL_INCLUDED
#define SDL_INCLUDED

#define WIN_W		960
#define WIN_H		960

#define BLACK		0x00,0x00,0x00,0xFF
#define BLACK_HEX	0x000000FF
#define WHITE		0xFF,0xFF,0xFF,0xFF
#define RED			0xFF,0x00,0x00,0xFF
#define GREEN		0x00,0xFF,0x00,0xFF
#define BLUE		0x00,0x00,0xFF,0xFF

void sdl_init(void);
void sdl_do_events(void);
void sdl_begin_draw(void);
void sdl_end_draw(void);
void sdl_quit(void);

#endif // SDL_INCLUDED
