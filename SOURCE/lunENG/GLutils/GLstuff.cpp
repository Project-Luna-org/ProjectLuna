/* $Id: GLstuff.cpp
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
#include <SDL_opengl.h>
#include <SDL_image.h>

#include <glm.hpp>
#include <ext.hpp>

#include "../core/renderer.h"
#include "../core/tools.h"
#include "../core/main.h"




using namespace std;
using namespace glm;


unsigned int loadTexture(string filename)
{
   unsigned int num=0;


   SDL_Surface *img=IMG_Load(stringchar(filename));
   

   if (!img) error("[loadTexture] file "+filename+" load failed!");


   Uint32 rmask, gmask, bmask, amask;

    /* SDL interprets each pixel as a 32-bit number, so our masks must depend
       on the endianness (byte order) of the machine */
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif

   SDL_Surface *img3 = SDL_CreateRGBSurface(0, 10, 10, 32,
                                   rmask, gmask, bmask, amask);


   SDL_PixelFormat *fmt = img3->format;

   SDL_Surface *img2=SDL_ConvertSurface(img,fmt,0);


   if (!img2) error("[loadTexture] file "+filename+" convertion failed!");

   

   
   glGenTextures(1,&num);

   glBindTexture(GL_TEXTURE_2D,num);

   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);


   //glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
   //glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);



   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);


   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img2->w, img2->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, img2->pixels);

   SDL_FreeSurface(img);
   SDL_FreeSurface(img2);

   return num;
}




void TraceError( )
{
	for ( GLenum Error = glGetError( ); ( GL_NO_ERROR != Error ); Error = glGetError( ) )
    {
      switch ( Error )
                {
                    case GL_INVALID_ENUM:      error(  "GL_INVALID_ENUM"      );  break;
                    case GL_INVALID_VALUE:     error(  "GL_INVALID_VALUE"     );  break;
                    case GL_INVALID_OPERATION: error(  "GL_INVALID_OPERATION" );  break;
                    case GL_STACK_OVERFLOW:    error(  "GL_STACK_OVERFLOW"    );  break;
                    case GL_STACK_UNDERFLOW:   error(  "GL_STACK_UNDERFLOW"   );  break;
                    case GL_OUT_OF_MEMORY:     error(  "GL_OUT_OF_MEMORY"     );  break;
                    default: break;
                }
           }
        
}



void CheckFramebufferStatus()
{
    
            switch ( glCheckFramebufferStatus( GL_FRAMEBUFFER ) )
            {
                case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:         error( "GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT"         ); break;
                case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT: error( "GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT" ); break;
                case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:        error( "GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER"        ); break;
                case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:        error( "GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER"        ); break;
                case GL_FRAMEBUFFER_UNSUPPORTED:                   error( "GL_FRAMEBUFFER_UNSUPPORTED"                   ); break;
                case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:        error( "GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE"        ); break;
                case GL_FRAMEBUFFER_UNDEFINED:                     error( "GL_FRAMEBUFFER_UNDEFINED"                     ); break;
                default: break;
            }
}



unsigned int createTexture(int w,int h)
{
	
	unsigned int textureID;

	glGenTextures(1,&textureID);
	
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA, w,h,0,GL_RGBA,GL_UNSIGNED_BYTE,NULL);
	

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);

	glBindTexture(GL_TEXTURE_2D, 0);

	return textureID;

}

