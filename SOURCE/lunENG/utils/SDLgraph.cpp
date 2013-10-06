

#include <SDL.h>

#include "SDLgraph.h"




unsigned int SetRGB32(unsigned char r, unsigned char g,unsigned char b)
{
	return (( b << 16 ) | ( g << 8 ) | r );
}

void GetRGB32(unsigned int c, unsigned char &r, unsigned char &g, unsigned char &b)
{
	b = (( c >> 16 ) & 0xFF);
	g = ( (c >> 8) & 0xFF );
	r = (c & 0xFF );
}



Uint32 getpixel32(SDL_Surface *surface, int x, int y)
{
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * 4;
    return *(Uint32 *)p;
}
	

void putpixel32(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * 4;
    *(Uint32 *)p = pixel;
}