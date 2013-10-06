#define NO_SDL_GLEXT

#include <Windows.h>
#include <glew.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <string>

#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>

#include <glm.hpp>
#include <ext.hpp>

#include "core/tools.h"
#include "core/main.h"
#include "utils\setup.h"
#include "GLutils/GLstuff.h"
#include "core\renderer.h"

#include "shaderToy.h"


using namespace std;
using namespace glm;



float curtime=0;

// unsigned int vao = 0;

renderer* shaderToyrenderer = NULL;
shader* shaderToyshader = NULL;

void initQuad()
{

	shaderToyshader = new shader(DATAfolder+"shader/shaderToy.vert",DATAfolder+"shader/flame.frag");

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


		

	shaderToyrenderer = new renderer(GL_STATIC_DRAW,GL_TRIANGLE_FAN,4);
	shaderToyrenderer->LoadPoints(v,12);







	/*
		glGenBuffers (1, &PointsVBO);
		glBindBuffer (GL_ARRAY_BUFFER, PointsVBO);
		glBufferData (GL_ARRAY_BUFFER,  12 * sizeof (float), &v, GL_STATIC_DRAW);

	
		glGenVertexArrays (1, &vao);
		glBindVertexArray (vao);
		glBindBuffer (GL_ARRAY_BUFFER, PointsVBO);
		glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);

	glEnableVertexAttribArray (0);

	glBindBuffer (GL_ARRAY_BUFFER, 0);
	glBindVertexArray (0);
	*/



}

void closeQuad()
{
	//	glDeleteVertexArrays(1,&vao);

	shaderToyrenderer->~renderer();
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

	


	/// glBindVertexArray (vao);


		 shaderToyrenderer->Render(shaderToyshader->prog);



		glUseProgram(0);




  	
}