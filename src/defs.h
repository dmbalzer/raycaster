#ifndef DEFS_INCLUDED
#define DEFS_INCLUDED

/* WINDOW */
#define WINDOW_W	960
#define WINDOW_H	640

/* COLORS */
#define BLACK		0x00,0x00,0x00,0xFF
#define WHITE		0xFF,0xFF,0xFF,0xFF
#define RED			0xFF,0x00,0x00,0xFF
#define GREEN		0x00,0xFF,0x00,0xFF
#define BLUE		0x00,0x00,0xFF,0xFF

/* MAP */
#define MAP_W		15
#define MAP_H		11
#define TILE_SIZE	24

/* PLAYER */
#define FOV DEG2RAD * 60

/* SCREEN */
#define SCREEN_W 240
#define SCREEN_H 160

/* INPUT */
#define LEFT  0
#define RIGHT 1
#define UP    2
#define DOWN  3

#endif // DEFS_INCLUDED
