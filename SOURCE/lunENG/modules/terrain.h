/* $Id: terrain.h 
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
 * @file terrain.h
 *
 * @brief      generates a Terrain from a HeightMap <p/> <br/> 
 *
 */


#pragma once

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
#include <time.h>

#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <glm.hpp>
#include <ext.hpp>

 
using namespace glm;




/**
 * @brief      generates a Terrain from a HeightMap <p/> <br/> 
 *
 */
class Terrain
{
public:
 
/**
 * @brief      generates a Terrain from a HeightMap <p/> <br/> 
  *
 * @param      theheightScale     the multiply factor of the Height of the Terrain Points <p/> <br/> 
 * @param      theblockScale	  the grid size (X*Z) of the terrain​ <p/> <br/> 
 *
 */
    Terrain(float theheightScale, float theblockScale);

/**
 * @brief      clean up <p/> <br/> 
 *
 */
   ~Terrain();



/**
 * @brief      Create teh Terrain form a Height Map <p/> <br/> 
 *
 */
	void LoadHeightMap(SDL_Surface* heightmap);


/**
 * @brief      the width of the Terrain in Heightmap pixels <p/> <br/> 
 *
 */
    unsigned int width;

/**
 * @brief      the breight of the Terrain in Heightmap pixels <p/> <br/> 
 *
 */
	unsigned int breight;


/**
 * @brief      howmuch Vertex to draw in GL_TRIANGLES mode <p/> <br/> 
 *
 */
	unsigned int numVertex;


/**
 * @brief    the Buffer to load in the Renderer (Points)  <p/> <br/> 
 *
 */
	float* PositionBuffer;

/**
 * @brief    the Buffer to load in the Renderer (Texture Coordinates)    <p/> <br/> 
 *
 */
	float* TextureBuffer;




private:


	float HeightScale;
	float BlockScale;


	vec3* TerrainPositions;
	vec2* TerrainTexture;


};