/* $Id: drawfont.cpp
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

#include <glm.hpp>
#include <ext.hpp>

using namespace std;
using namespace glm;


#include "GLstuff.h"
#include "../core/tools.h"
#include "../utils/SDLgraph.h"
#include "../utils/setup.h"
#include "../core/renderer.h"
#include "shader.h"
#include "drawfont.h"





int drawfont::doround(double x)
{
	return (int)(x + 0.5);
}

int drawfont::nextpoweroftwo(float x)
{
	double logbase2 = log(x) / log(2.0f);
	return doround(std::pow(2,ceil(logbase2)));
}

void drawfont::glTextOut(int x, int y, string txt, Uint32 color)
{
    
    string tempstr = txt;
    
    if (strlength(tempstr)==0) return;
    

	if (!curfont) error("glTextOut: font is not initialized!");

	SDL_Color tmpfontcolor;
    Uint8 r,g,b;

    r=0;
    g=0;
    b=0;
    
	GetRGB32(color,r,g,b);

    
    tmpfontcolor.r = r;
    tmpfontcolor.g = g;
    tmpfontcolor.b = b;


	SDL_Surface *resulting_text;
    
    resulting_text = TTF_RenderText_Blended(curfont,tempstr.c_str(), tmpfontcolor);
	
    if (!resulting_text) error("glTextOut: TTF_RenderText_Blended fails: "+ (string) SDL_GetError());


	int w = resulting_text->w;
	int h = resulting_text->h;


	SDL_Surface* intermediary = SDL_CreateRGBSurface(0, w, h, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);

	if (!intermediary) error("glTextOut: SDL_CreateRGBSurface fails: "+ (string) SDL_GetError());

	SDL_BlitSurface(resulting_text, 0, intermediary, 0);

	SDL_FreeSurface(resulting_text);


	
	
        glGenTextures( 1, &texture );
			
		
		glBlendFunc(GL_ONE, GL_ONE);
		glEnable(GL_BLEND);
		
		
    
        glBindTexture( GL_TEXTURE_2D, texture );
        

		

        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
        
		
		

		
        glTexImage2D( GL_TEXTURE_2D, 0,GL_RGBA, intermediary->w, intermediary->h, 0, 
                      GL_BGRA, GL_UNSIGNED_BYTE, intermediary->pixels );


        SDL_FreeSurface( intermediary );
	
 


	float v[] = {
					(float) x+0, (float) y+0, 0,			
					(float) x+w, (float) y+0, 0,
					(float) x+w, (float) y+h, 0,
					(float) x+0, (float) y+h, 0
				};	



	float t[] = {
					0,0,
					1,0,
					1,1,
					0,1
				};

         


	renderer* fontrenderer =  new renderer(GL_STREAM_DRAW,GL_TRIANGLE_FAN,FontShader->prog);
	fontrenderer->setNumVertex(4);
	fontrenderer->LoadPoints(v,12);
	fontrenderer->LoadTextCoords(t,8);



	glUseProgram(FontShader->prog);

	


		mat4 ProjMatrix = mat4(1);
		ProjMatrix = ortho<float>(0.0f, (float) screenwidth, (float) screenheight, 0, -1.0f, 1.0f);


		mat4 matrix = ProjMatrix;
		int matrix_location = glGetUniformLocation (FontShader->prog, "matrix");
		glUniformMatrix4fv (matrix_location, 1, GL_FALSE, value_ptr(matrix));



	fontrenderer->Render();



	




	glUseProgram(0);

	glDisable(GL_BLEND);
	glDeleteTextures( 1, &texture );


	fontrenderer->~renderer();



	
}


drawfont::drawfont(string fontfilename,int size)
:curfont(NULL), texture(0), FontShader(NULL)
{
		
	if (!(curfont = TTF_OpenFont(stringchar(fontfilename), size))) error("TTF_OpenFont "+fontfilename+" fails: " + (string) SDL_GetError());

    if (rendererver == 1)
	 FontShader = new shader(DATAfolder+"shader/2.1/through.vert", DATAfolder+"shader/2.1/through.frag");
    if (rendererver == 2)
     FontShader = new shader(DATAfolder+"shader/3.2/through.vert", DATAfolder+"shader/3.2/through.frag");
    if (rendererver == 3)
     FontShader = new shader(DATAfolder+"shader/4.3/through.vert", DATAfolder+"shader/4.3/through.frag");
    
}

drawfont::~drawfont()
{
	TTF_CloseFont(curfont);
	FontShader->~shader();
}
