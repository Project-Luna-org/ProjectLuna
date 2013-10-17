/* $Id: SDLgraph.cpp
   Copyright (C) 2013 Kirill Kranz

  This source is free software; you can redistribute it and/or modify it under
  the terms of the GNU General Public License as published by the Free
  Software Foundation; either version 2 of the License, or (at your option)
  any later version.

  This code is distributed in the hope that it will be useful, but WITHOUT ANY
  WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
  FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
  details.

  A copy of the GNU General Public License is available on the World Wide Web
  at <http://www.gnu.org/copyleft/gpl.html>. You can also obtain it by writing
  to the Free Software Foundation, Inc., 59 Temple Place - Suite 330, Boston,
  MA 02111-1307, USA.
*/

#include <string>

#include <SDL.h>
#include <SDL_image.h>
#include "../core/tools.h"
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
	if (!img) error("error loading "+filename);
	img = SDL_ConvertSurfaceFormat(img,SDL_PIXELFORMAT_ARGB8888,0);
	return img;
}