/* $Id: sprites.cpp
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

#include "GLstuff.h"
#include "../utils/setup.h"
#include "../core/renderer.h"
#include "shader.h"

#include "sprites.h"

using namespace std;
using namespace glm;

sprites::sprites()
{

	if (rendererver == 1)
	 SpriteShader = new shader(DATAfolder+"shader/2.1/through.vert", DATAfolder+"shader/2.1/through.frag");
    if (rendererver == 2)
     SpriteShader = new shader(DATAfolder+"shader/3.2/through.vert", DATAfolder+"shader/3.2/through.frag");
    if (rendererver == 3)
     SpriteShader = new shader(DATAfolder+"shader/4.3/through.vert", DATAfolder+"shader/4.3/through.frag");
    
	
}

sprites::~sprites()
{
	SpriteShader->~shader();
}



void sprites::drawSprite(int x,int y, SDL_Surface* img)
{

	SDL_Surface* go=img;

	 go=SDL_ConvertSurfaceFormat(go,SDL_PIXELFORMAT_ARGB8888,0);
	 

	unsigned int texture;

		glGenTextures( 1, &texture );
			
		
		glBlendFunc(GL_ONE, GL_ONE);
		glEnable(GL_BLEND);
		
		
    
        glBindTexture( GL_TEXTURE_2D, texture );
        

		

        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
        
		
		

        glTexImage2D( GL_TEXTURE_2D, 0,GL_RGBA, img->w, img->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, go->pixels );
		
	

	float v[] = {
					(float) x+0, (float) y+0, 0,			
					(float) x+img->w, (float) y+0, 0,
					(float) x+img->w, (float) y+img->h, 0,
					(float) x+0, (float) y+img->h, 0
				};	



	float t[] = {
					0,0,
					1,0,
					1,1,
					0,1
				};

         
	

	renderer* spriterenderer =  new renderer(GL_STREAM_DRAW,GL_TRIANGLE_FAN,SpriteShader->prog);
	spriterenderer->setNumVertex(4);

	spriterenderer->LoadPoints(v,12);
	spriterenderer->LoadTextCoords(t,8);



	glUseProgram(SpriteShader->prog);

	


		mat4 ProjMatrix = mat4(1);
		ProjMatrix = ortho<float>(0.0f, (float) screenwidth, (float) screenheight, 0, -1.0f, 1.0f);


		mat4 matrix = ProjMatrix;
		int matrix_location = glGetUniformLocation (SpriteShader->prog, "matrix");
		glUniformMatrix4fv (matrix_location, 1, GL_FALSE, value_ptr(matrix));


	
	spriterenderer->Render();




	glUseProgram(0);

	glDisable(GL_BLEND);
	glDeleteTextures( 1, &texture );


	spriterenderer->~renderer();


}
