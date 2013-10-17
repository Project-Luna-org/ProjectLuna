/* $Id: shader.h 
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
 * @file shader.h
 *
 * @brief      manages a shader <p/> <br/> 
 * @details    stores a vertex and a fragment shader in strings, compiles thouse to a ID and links this to a program<p/> <br/> 
 *    		   
 */





#pragma once

#include <string>

using namespace std;




/**
 * @brief   use this class to manage a shader pair <p/> <br/> 
 * @details <p/> <br/> you must specify a full path to a vertex and a fragment shader.
 *		         <br/> a shader Program will be compiled<p/> <br/> 
 *
 */
class shader
{
public:

/**
 * @brief      the actual ID of the shader program <p/> <br/> 
 *
 * @details <p/> <br/>  Use this ID to swich the current shader <br/>
 */
	unsigned int prog;




/**
 * @brief      load and compile the shaders <p/> <br/> 
 *
 * @details    if a shader has any errors, the compiler will return an error() which will terminate the application after a visible message<br/>
 *
 * @param      filenameVertexShader     loads a Vertex shader from the given path
 * @param      filenameFragmentShader	loads a Fragment shader from the given path
 *
 *
 */
	shader(string filenameVertexShader, string filenameFragmentShader); 

/**
 * @brief      clean up the memory <p/> <br/> 
 *
 */
   ~shader();


 /**
 * @brief      sets this shader to the current <p/> <br/> 
 *
 * @details    it is just a call to glUseProgram(prog); <br/>
 *
 */
   void useShader();

 /**
 * @brief      swiches the current shader off <p/> <br/> 
 *
 * @details    it is just a call to glUseProgram(0); <br/>
 *
 */
   void delShader();





private:
	
	string vsSource;
	string fsSource;
	unsigned int vsID;
	unsigned int fsID;

};