/* $Id: shader.cpp
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
#include <stdlib.h>
#include <fstream>

#include <SDL.h>
#include <SDL_opengl.h>


using namespace std;

#include "../core/tools.h"
#include "shader.h"




shader::shader(string filenameVertexShader, string filenameFragmentShader)
{
	ifstream inputVSfile(stringchar(filenameVertexShader));

	if (!inputVSfile) error("[shader] Error opening Vertex Shader File "+filenameFragmentShader);

	vsSource="";
	char ch[256];
	while(!inputVSfile.eof())
	{
		inputVSfile.getline(ch,256);
		vsSource+=ch;
		vsSource+="\n";
	}
	inputVSfile.close();






		vsID=glCreateShader(GL_VERTEX_SHADER);

		const char* VSsource=vsSource.c_str();

			
		glShaderSource(vsID,1,&VSsource,NULL);

		glCompileShader(vsID);


		GLint shaderCompiled;

		glGetShaderiv(vsID, GL_COMPILE_STATUS, &shaderCompiled);
		if(shaderCompiled == GL_FALSE)
		{
			char errorbuff[256];
			glGetShaderInfoLog(vsID,256,NULL,errorbuff);

			error("ERROR: "+filenameVertexShader+"\n"+errorbuff);
		}


	


	ifstream inputFSfile(stringchar(filenameFragmentShader));

	if (!inputFSfile) error("[shader] Error opening Fragment Shader File "+filenameFragmentShader);

	fsSource="";
	
	while(!inputFSfile.eof())
	{
		inputFSfile.getline(ch,256);
		fsSource+=ch;
		fsSource+="\n";
	}
	inputFSfile.close();

		fsID=glCreateShader(GL_FRAGMENT_SHADER);

		const char* FSsource=fsSource.c_str();

		glShaderSource(fsID,1,&FSsource,NULL);

		glCompileShader(fsID);


		glGetShaderiv(fsID, GL_COMPILE_STATUS, &shaderCompiled);
		if(shaderCompiled == GL_FALSE)
		{

			char errorbuff[256];
			glGetShaderInfoLog(fsID,256,NULL,errorbuff);

			error("ERROR: "+filenameFragmentShader+"\n"+errorbuff);
		}




		prog=glCreateProgram();

		


		glAttachShader(prog,vsID);
		glAttachShader(prog,fsID);

		glLinkProgram(prog);
    
    
    int IsLinked;
    glGetProgramiv(prog, GL_LINK_STATUS, (int *)&IsLinked);
    if(IsLinked == GL_FALSE)
    {
       
        char errorbuff[256];
        
        glGetProgramInfoLog(prog,256,NULL,errorbuff);
        
        error("ERROR: "+filenameFragmentShader+"\n"+filenameVertexShader+"\n"+"PROGRAM\n"+errorbuff);
    }

	
}

shader::~shader()
{
	glDetachShader(prog,vsID);
	glDetachShader(prog,fsID);
	glDeleteShader(vsID);
	glDeleteShader(fsID);
	glDeleteProgram(prog);
}


  
void shader::useShader()
{
	glUseProgram(prog);
}


void shader::delShader()
{
	glUseProgram(0);
}