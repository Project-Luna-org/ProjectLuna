/* $Id: renderer.cpp
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

#include "tools.h"
#include "main.h"
#include "../utils/setup.h"
#include "../GLutils/GLstuff.h"
#include "../utils/setup.h"
#include "renderer.h"


using namespace std;
using namespace glm;



renderer::renderer(unsigned int drawingMode, unsigned int PrimitiveType, unsigned int shaderProc)
{

	PointsVBO = 0;
	numPoints = 0;
	attributePoints = -1;

	UVsVBO = 0;
	numUVs = 0;
	attributeUVs = -1;

	this->drawingMode = drawingMode;
	this->PrimitiveType = PrimitiveType;
    this->shaderProc = shaderProc;
    
    if (rendererver==2) glGenVertexArrays(1, &VAO);
	if (rendererver==3) glGenVertexArrays(1, &VAO);
    
}

void renderer::setNumVertex(unsigned int numVertex)
{
		this->numVertex =  numVertex;

}

renderer::~renderer()
{
	glDeleteBuffers(1,&PointsVBO);
	if (UVsVBO)	glDeleteBuffers(1,&UVsVBO);
    if (rendererver==2) glDeleteVertexArrays(1,&VAO);
	if (rendererver==3) glDeleteVertexArrays(1,&VAO);
}


void renderer::LoadPoints(void* data,unsigned int numPoints)
{

	this->numPoints = numPoints;


	if (rendererver==2) glBindVertexArray(VAO);
	if (rendererver==3) glBindVertexArray(VAO);
    
		glGenBuffers (1, &PointsVBO);
		glBindBuffer (GL_ARRAY_BUFFER, PointsVBO);

		glBufferData (GL_ARRAY_BUFFER,  numPoints * sizeof (float) , data, drawingMode);
	
    if (rendererver==2)
    {
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    }

    if (rendererver==3)
    {
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    }   

		glBindBuffer(GL_ARRAY_BUFFER,0);
    
    	if (rendererver==2) glBindVertexArray(0);
		if (rendererver==3) glBindVertexArray(0);
    
    if (rendererver == 1)
    {
        
 		loc_inVertex = -1;
		loc_inVertex = glGetAttribLocation(shaderProc, "inVertex");
		if (loc_inVertex==-1) error("loc_inVertex = -1");
        
    }
    
    

}



void renderer::LoadTextCoords(void* data, unsigned int numUVs)
{
	
		this->numUVs = numUVs;
    
    
    	if (rendererver==2) glBindVertexArray(VAO);
		if (rendererver==3) glBindVertexArray(VAO);
    
    

		glGenBuffers (1, &UVsVBO);

		glBindBuffer(GL_ARRAY_BUFFER, UVsVBO);
		
		glBufferData (GL_ARRAY_BUFFER,  numUVs * sizeof (float), data, drawingMode);
    
    if (rendererver==2)
    {
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
    }

    if (rendererver==3)
    {
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
    }


		glBindBuffer(GL_ARRAY_BUFFER,0);
        if (rendererver==2) glBindVertexArray(0);
		if (rendererver==3) glBindVertexArray(0);
    
    if (rendererver == 1)
    {
    	loc_inTextCoords=-1;
        loc_inTextCoords = glGetAttribLocation(shaderProc, "inTextCoords");
        if (loc_inTextCoords==-1) error("loc_inTextCoords = -1");
    }
    
    
}



void renderer::Render()
{

 if (rendererver == 1)
 {
		glEnableVertexAttribArray(loc_inVertex);
		glBindBuffer(GL_ARRAY_BUFFER, PointsVBO);
		glVertexAttribPointer(loc_inVertex, 3, GL_FLOAT, GL_FALSE, 0, 0);

	
		if (UVsVBO)
		{
			glEnableVertexAttribArray(loc_inTextCoords);
			glBindBuffer(GL_ARRAY_BUFFER, UVsVBO);
			glVertexAttribPointer(loc_inTextCoords, 2, GL_FLOAT, GL_FALSE, 0, 0);
		}


  
        glDrawArrays (PrimitiveType, 0, numVertex); 
		

		glDisableVertexAttribArray(loc_inVertex);
		if (UVsVBO) glDisableVertexAttribArray(loc_inTextCoords);

			
		glBindBuffer(GL_ARRAY_BUFFER, 0);
 }
    
 if (rendererver == 2)
 {  
        glBindVertexArray(VAO);
        glDrawArrays (PrimitiveType, 0, numVertex);
 }
    
 if (rendererver == 3)
 {  
        glBindVertexArray(VAO);
        glDrawArrays (PrimitiveType, 0, numVertex);
 }
}
