/* $Id: drawfont.h 
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
 * @file drawfont.h
 *
 * @brief      draws a string on the display with a given position <p/> <br/> 
 * @details    The font size is fixed by the initialisation and can not been changed after it.<p/> <br/> 
 *   		   this module expects the "through shader" in the shader directory. <br/>
 *			   it means you must have setuped the DATAfolder variable properly to your DATA folder <br/>
 *			   than you must have setuped the renderver variable to 1,2 or 3 to chose the GLSL version <br/>
 *			   and you must have, depends on the setuped GLSL version, the proper folder with the <br/>
 *			   through.vert and through.frag shaders <br/>
 */




#pragma once
#define NO_SDL_GLEXT

#include "../osSetup.h"

#ifdef OS_WIN
 #include <Windows.h>
#endif

#include <glew.h>

#ifdef OS_OSX
 #include <OpenGL/OpenGL.h>
#endif
#ifdef OS_WIN
 #include <gl/GL.h>
 #include <gl/GLU.h>
#endif

#include <string>
#include <SDL.h>
#include <SDL_ttf.h>

#include "shader.h"

using namespace std;



/**
 * @brief   use this class to draw a string on the display <p/> <br/> 
 * @details <p/> <br/> you must follow the folowing rules:
 *		<br/>	The font size is fixed by the initialisation and can not been changed after it.<p/> <br/> 
 *   				this module expects the "through shader" in the shader directory. <br/>
 *					it means you must have setuped the DATAfolder variable properly to your DATA folder <br/>
 *					than you must have setuped the renderver variable to 1,2 or 3 to chose the GLSL version <br/>
 *					and you must have, depends on the setuped GLSL version, the proper folder with the <br/>
 *					through.vert and through.frag shaders <br/>	
 *			<p/>    the constructor loads a TrueTypeFontFile with the given size, than you can blit <br/>
 *					using the glTextOut function on the current OpenGL rendering context
 */
class drawfont
{
public:


/**
 * @brief      load the TrueTypeFile by a full path to it and set the size
 *
 * @details    this module expects the "through shader" in the shader directory. <br/>
 *			   it means you must have setuped the DATAfolder variable properly to your DATA folder <br/>
 *			   than you must have setuped the renderver variable to 1,2 or 3 to chose the GLSL version <br/>
 *			   and you must have, depends on the setuped GLSL version, the proper folder with the <br/>
 *			   through.vert and through.frag shaders <br/>
 *             
 *
 * @param      fontfilename     full path to a .ttf file
 * @param      size			    the fixed size of the font
 *
 *
 * @see        void glTextOut(int x, int y, string txt, Uint32 color);
 */
	drawfont(string fontfilename, int size);


/**
 * @brief      cleans the memory of this class
 *
 */
   ~drawfont();



/**
 * @brief      draws a string on the given position with a given color on the display
 *
 * @details    the coordinates a are: 0,0 is the left upper corner<br/>
 *			   and the maximum x is the screen width and the maximum y is the screen height, so the lower right corner <br/>
 *
 * @param      x     set the X position on the screen
 * @param      y	 set the Y position on the screen
 * @param      txt	 the string to display
 * @param      color	the color of the letters
 *
 *
 */
	void glTextOut(int x, int y, string txt, Uint32 color);






private:

	drawfont& operator=(const drawfont&) const;
	drawfont(const drawfont&);
	
	TTF_Font* curfont;
	GLuint texture;

	shader* FontShader;


	int doround(double x);
	int nextpoweroftwo(float x);


};
