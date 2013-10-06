#pragma once
#include <SDL.h>


unsigned int RGB32(unsigned char r, unsigned char g,unsigned char b);
void GetRGB32(unsigned int c, unsigned char &r, unsigned char &g, unsigned char &b);


Uint32 getpixel32( SDL_Surface *surface, int x, int y );
void putpixel32( SDL_Surface *surface, int x, int y, Uint32 pixel );