/* $Id: sprites.h 
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
 * @file sprites.h
 *
 * @brief      manages a sprite <p/> <br/> 
 * @details    it is clever to make one instance of this class and use it to dieplay evry sprite<p/> <br/> 
 *   		   this module expects the "through shader" in the shader directory. <br/>
 *			   it means you must have setuped the DATAfolder variable properly to your DATA folder <br/>
 *			   than you must have setuped the renderver variable to 1,2 or 3 to chose the GLSL version <br/>
 *			   and you must have, depends on the setuped GLSL version, the proper folder with the <br/>
 *			   through.vert and through.frag shaders <br/>
 */


#pragma once

#include <SDL.h>
#include "shader.h"




/**
 * @brief     loads the shaders needed for a sprite blit operation <p/> <br/> 
 *    		   
 */
class sprites
{
	public:
		
/**
 * @brief      loads the shaders needed for a sprite blit operation <p/> <br/> 
 *
 * @details    this module expects the "through shader" in the shader directory. <br/>
 *			   it means you must have setuped the DATAfolder variable properly to your DATA folder <br/>
 *			   than you must have setuped the renderver variable to 1,2 or 3 to chose the GLSL version <br/>
 *			   and you must have, depends on the setuped GLSL version, the proper folder with the <br/>
 *			   through.vert and through.frag shaders <br/>
 */		
		sprites();


/**
 * @brief      cleans the memory of ths class
 *
 */
	   ~sprites();





/**
 * @brief      draws a sprite on the given position on the display
 *
 * @details    the coordinates a are: 0,0 is the left upper corner<br/>
 *			   and the maximum x is the screen width and the maximum y is the screen height, so the lower right corner <br/>
 *
 * @param      x     set the X position on the screen
 * @param      y	 set the Y position on the screen
 * @param      img	 a sprite in the SDL_Image
 *
 *
 */
		void drawSprite(int x,int y, SDL_Surface* img);




	private:

		
		sprites& operator=(const sprites&) const;
		sprites(const sprites&);	

		shader* SpriteShader;
};













