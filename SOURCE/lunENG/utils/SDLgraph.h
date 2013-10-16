#pragma once
#include <SDL.h>
#include <string>

unsigned int RGB32(unsigned char r, unsigned char g,unsigned char b);
void GetRGB32(unsigned int c, unsigned char &r, unsigned char &g, unsigned char &b);

unsigned int RGBA32(unsigned char r, unsigned char g,unsigned char b, unsigned char a);
void GetRGBA32(unsigned int c, unsigned char &r, unsigned char &g, unsigned char &b, unsigned char &a);



Uint32 getpixel32( SDL_Surface *surface, int x, int y );
void putpixel32( SDL_Surface *surface, int x, int y, Uint32 pixel );


SDL_Surface* LoadIMG(std::string filename);