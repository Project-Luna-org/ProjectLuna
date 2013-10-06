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

#include "tools.h"
#include "main.h"
#include "../utils/setup.h"
#include "../GLutils/GLstuff.h"
#include "../utils/setup.h"
#include "renderer.h"


using namespace std;
using namespace glm;



renderer::renderer(unsigned int drawingMode, unsigned int PrimitiveType,unsigned int numVertex)
{

	PointsVBO = 0;
	numPoints = 0;
	attributePoints = -1;

	UVsVBO = 0;
	numUVs = 0;
	attributeUVs = -1;

	this->drawingMode = drawingMode;
	this->PrimitiveType = PrimitiveType;
	this->numVertex =  numVertex;
}

renderer::~renderer()
{
	glDeleteBuffers(1,&PointsVBO);
	if (UVsVBO)	glDeleteBuffers(1,&UVsVBO);
}


void renderer::LoadPoints(void* data,unsigned int numPoints)
{

	this->numPoints = numPoints;


	
		glGenBuffers (1, &PointsVBO);
		glBindBuffer(GL_ARRAY_BUFFER, PointsVBO);

		glBufferData (GL_ARRAY_BUFFER,  numPoints * sizeof (float), data, drawingMode);
	

		glBindBuffer(GL_ARRAY_BUFFER,0);

}



void renderer::LoadTextCoords(void* data, unsigned int numUVs)
{
	
		this->numUVs = numUVs;

		glGenBuffers (1, &UVsVBO);

		glBindBuffer(GL_ARRAY_BUFFER, UVsVBO);
		
		glBufferData (GL_ARRAY_BUFFER,  numUVs * sizeof (float), data, drawingMode);

		glBindBuffer(GL_ARRAY_BUFFER,0);
	
}



void renderer::Render(unsigned int shaderProc)
{

	/*
		glEnableClientState(GL_VERTEX_ARRAY);
		glBindBuffer(GL_ARRAY_BUFFER, PointsVBO);
		glVertexPointer(3, GL_FLOAT, 0, 0);
	
		if (UVsVBO) glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		if (UVsVBO) glBindBuffer(GL_ARRAY_BUFFER, UVsVBO);
		if (UVsVBO) glTexCoordPointer(2, GL_FLOAT, 0, 0);

	
        glDrawArrays (PrimitiveType, 0, numVertex); 
		

		
		if (UVsVBO) glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
		
		*/


		GLint loc_inVertex = -1;
		loc_inVertex = glGetAttribLocation(shaderProc, "inVertex");
		if (loc_inVertex==-1) error("loc_inVertex = -1");
		glEnableVertexAttribArray(loc_inVertex);
		glBindBuffer(GL_ARRAY_BUFFER, PointsVBO);
		glVertexAttribPointer(loc_inVertex, 3, GL_FLOAT, GL_FALSE, 0, 0);

		GLint loc_inTextCoords=-1;
		if (UVsVBO)
		{
		    loc_inTextCoords = glGetAttribLocation(shaderProc, "inTextCoords");
			if (loc_inTextCoords==-1) error("loc_inTextCoords = -1");
			glEnableVertexAttribArray(loc_inTextCoords);
			glBindBuffer(GL_ARRAY_BUFFER, UVsVBO);
			glVertexAttribPointer(loc_inTextCoords, 2, GL_FLOAT, GL_FALSE, 0, 0);
		}


  
        glDrawArrays (PrimitiveType, 0, numVertex); 
		

		glDisableVertexAttribArray(loc_inVertex);
		if (UVsVBO) glDisableVertexAttribArray(loc_inTextCoords);

			
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		
}
