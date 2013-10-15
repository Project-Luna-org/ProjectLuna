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

         
	

	renderer* spriterenderer =  new renderer(GL_STREAM_DRAW,GL_TRIANGLE_FAN,4,SpriteShader->prog);

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
