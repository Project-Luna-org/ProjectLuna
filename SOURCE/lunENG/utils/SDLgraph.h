/* $Id: SDLgraph.h 
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


/**
 * @file SDLgraph.h
 *
 * @brief      some SDL-Graphic-Tools <p/> <br/>
 * @details    
 */


#pragma once

#include <SDL.h>
#include <string>


/**
 * @brief  packs the Red, Green and the Blue channels in a 32bpp Color  <p/> <br/> 
 */
unsigned int RGB32(unsigned char r, unsigned char g,unsigned char b);

/**
 * @brief  extractss the Red, Green and the Blue channels from a 32bpp Color  <p/> <br/> 
 */
void GetRGB32(unsigned int c, unsigned char &r, unsigned char &g, unsigned char &b);


/**
 * @brief  packs the Red, Green, Blue and the Alpha channels in a 32bpp Color  <p/> <br/> 
 */
unsigned int RGBA32(unsigned char r, unsigned char g,unsigned char b, unsigned char a);

/**
 * @brief  extractss the Red, Green, Blue and the Alpha channels from a 32bpp Color  <p/> <br/> 
 */
void GetRGBA32(unsigned int c, unsigned char &r, unsigned char &g, unsigned char &b, unsigned char &a);


/**
 * @brief  retruns a packed 32bpp Color from the X and the Y position from a SDL Surface <p/> <br/> 
 */
Uint32 getpixel32( SDL_Surface *surface, int x, int y );

/**
 * @brief  sets a packed 32bpp Color to the X and the Y position of a SDL Surface <p/> <br/> 
 */
void putpixel32( SDL_Surface *surface, int x, int y, Uint32 pixel );

/**
 * @brief  loads an Image from a File to a SDL Surface <p/> <br/> 
 */
SDL_Surface* LoadIMG(std::string filename);