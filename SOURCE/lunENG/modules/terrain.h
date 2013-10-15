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


class Terrain
{
public:
 
    Terrain(float theheightScale, float theblockScale);
   ~Terrain();

   void LoadHightMap(SDL_Surface* heightmap);

    unsigned int width;
	unsigned int breight;

	float HeightScale;
	float BlockScale;


	vec3* TerrainPositions;
	vec2* TerrainTexture;

	unsigned int numVertex;

	vec3* PositionBuffer;
	vec2* TextureBuffer;



};