#ifndef DEFS_INCLUDED
#define DEFS_INCLUDED

#define MAP_W 15
#define MAP_H 11
#define TILE_SIZE 32
#define WIN_W (MAP_W*TILE_SIZE)
#define WIN_H (MAP_H*TILE_SIZE)

#define PI 3.14159265358979323846f
#define DEG2RAD (PI/180.0f)

#define BLACK 0x00,0x00,0x00,0xFF
#define WHITE 0xFF,0xFF,0xFF,0xFF
#define GRAY  0x50,0x50,0x50,0xFF
#define RED   0xFF,0x00,0x00,0xFF
#define GREEN 0x00,0xFF,0x00,0xFF

#endif // DEFS_INCLUDED
