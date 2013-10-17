#define NO_SDL_GLEXT

#include "osSetup.h"

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

#include "core/tools.h"
#include "core/main.h"
#include "utils/setup.h"
#include "GLutils/GLstuff.h"
#include "core/renderer.h"

#include "shaderToy.h"


using namespace std;
using namespace glm;



float curtime=0;


renderer* shaderToyrenderer = NULL;
shader* shaderToyshader = NULL;

void initQuad()
{

    if (rendererver == 1)
        shaderToyshader = new shader(DATAfolder+"shader/2.1/shaderToy.vert",DATAfolder+"shader/2.1/flame.frag");
    if (rendererver == 2)
        shaderToyshader = new shader(DATAfolder+"shader/3.2/shaderToy.vert",DATAfolder+"shader/3.2/flame.frag");
    if (rendererver == 3)
        shaderToyshader = new shader(DATAfolder+"shader/4.3/shaderToy.vert",DATAfolder+"shader/4.3/flame.frag");
    

		int x=0;
		int y=0;
		int w=screenwidth;
		int h=screenheight;

		
	float v[] = {
					(float) x+0, (float) y+0, 0,			
					(float) x+w, (float) y+0, 0,
					(float) x+w, (float) y+h, 0,
					(float) x+0, (float) y+h, 0
				};	


		

	shaderToyrenderer = new renderer(GL_STATIC_DRAW,GL_TRIANGLE_FAN,shaderToyshader->prog);
	shaderToyrenderer->setNumVertex(4);
	shaderToyrenderer->LoadPoints(v,12);





}

void closeQuad()
{

	shaderToyrenderer->~renderer();
	shaderToyshader->~shader();
}

void drawQuad()
{

	 glUseProgram(shaderToyshader->prog);

	
		mat4 matrix = ortho<float>(0.0f, (float) screenwidth, (float) screenheight, 0, -1.0f, 1.0f);
	
		int matrix_location = glGetUniformLocation (shaderToyshader->prog, "matrix");
		if (matrix_location==-1) error("matrix");
		glUniformMatrix4fv (matrix_location, 1, GL_FALSE, value_ptr(matrix));

	
		
	curtime+=0.05f;

		GLint loc0 = glGetUniformLocation(shaderToyshader->prog, "iGlobalTime");
		if (loc0==-1) error("loc0 = -1");
		glUniform1f(loc0, curtime);

		GLint loc1 = glGetUniformLocation(shaderToyshader->prog, "iResolution");
		if (loc1==-1) error("loc1 = -1");
		glUniform3f(loc1, (float)screenwidth,(float)screenheight,0);

	



		 shaderToyrenderer->Render();



		glUseProgram(0);




  	
}
