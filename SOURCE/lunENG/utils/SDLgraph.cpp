#include <string>

#include <SDL.h>
#include <SDL_image.h>

#include "SDLgraph.h"

using namespace std;


unsigned int RGB32(unsigned char r, unsigned char g,unsigned char b)
{
	Uint32 color = (( b << 16 ) | ( g << 8 ) | r );

	if(SDL_BYTEORDER == SDL_BIG_ENDIAN) color =  SDL_Swap32(color);

	return color;
}

void GetRGB32(unsigned int c, unsigned char &r, unsigned char &g, unsigned char &b)
{
	Uint32 color=c;
    
	if(SDL_BYTEORDER == SDL_BIG_ENDIAN) color =  SDL_Swap32(color);

	b = (( color >> 16 ) & 0xFF);
	g = ((color >> 8) & 0xFF );
	r = (color & 0xFF );
}



unsigned int RGBA32(unsigned char r, unsigned char g,unsigned char b, unsigned char a)
{
	Uint32 color = (( a << 24 ) | ( b << 16 ) | ( g << 8 ) | r );

	if(SDL_BYTEORDER == SDL_BIG_ENDIAN) color =  SDL_Swap32(color);

	return color;

}

void GetRGBA32(unsigned int c, unsigned char &r, unsigned char &g, unsigned char &b, unsigned char &a)
{
	Uint32 color=c;
    
	if(SDL_BYTEORDER == SDL_BIG_ENDIAN) color =  SDL_Swap32(color);


	a = (( color >> 24 ) & 0xFF);
	b = (( color >> 16 ) & 0xFF);
	g = ((color >> 8) & 0xFF );
	r = (color & 0xFF );
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




SDL_Surface* LoadIMG(string filename)
{
	SDL_Surface* img;
	img = IMG_Load(filename.c_str());
	img = SDL_ConvertSurfaceFormat(img,SDL_PIXELFORMAT_ARGB8888,0);
	return img;
}