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
#include <time.h>

#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <glm.hpp>
#include <ext.hpp>

#include "../utils/SDLgraph.h"
#include "../utils/setup.h"
#include "../core/tools.h"
#include "../core/main.h"

#include "terrain.h"


using namespace std;
using namespace glm;


Terrain::Terrain(float theheightScale, float theblockScale)
{

	HeightScale = theheightScale;
	BlockScale = theblockScale;

}


Terrain::~Terrain()
{
}



void Terrain::LoadHeightMap(SDL_Surface* heightmap)
{

	width = heightmap->w;
	breight = heightmap->h;

	numVertex = width*breight;

	TerrainPositions = new vec3[numVertex];
	TerrainTexture = new vec2[numVertex];

	unsigned int index=0;
	for (unsigned int z=0;z<breight; z++)
	{
		for (unsigned int x=0; x<width; x++)
		{

			index=z*width+x;

			Uint8 h = *((Uint8*) heightmap->pixels+ z*heightmap->pitch+x*4);
			float height = (float)h / 255.0f;

			TerrainPositions[index].y=height * HeightScale;

			TerrainPositions[index].x=float(x) * BlockScale;
			TerrainPositions[index].z=float(z) * BlockScale;


			TerrainTexture[index].x = (float) x / (float) width;
			TerrainTexture[index].y = (float) z / (float) breight;


		
		}

	}




	numVertex = width*breight*2*3*3; 

    PositionBuffer = new float [numVertex];
	TextureBuffer = new float [numVertex];


	unsigned int i=0;
	for (unsigned int z=0;z<breight-1;z++)
		for (unsigned int x=0;x<width-1;x++)
		{
			//bottom triangle
			index=((z)*width)+(x);
			PositionBuffer[i++] = TerrainPositions[index].x;
			PositionBuffer[i++] = TerrainPositions[index].y;
			PositionBuffer[i++] = TerrainPositions[index].z;
			index=((z)*width)+(x+1);
			PositionBuffer[i++] = TerrainPositions[index].x;
			PositionBuffer[i++] = TerrainPositions[index].y;
			PositionBuffer[i++] = TerrainPositions[index].z;
			index=((z+1)*width)+(x+1);
			PositionBuffer[i++] = TerrainPositions[index].x;
			PositionBuffer[i++] = TerrainPositions[index].y;
			PositionBuffer[i++] = TerrainPositions[index].z;
			//top triangle
			index=((z)*width)+(x);
			PositionBuffer[i++] = TerrainPositions[index].x;
			PositionBuffer[i++] = TerrainPositions[index].y;
			PositionBuffer[i++] = TerrainPositions[index].z;
			index=((z+1)*width)+(x+1);
			PositionBuffer[i++] = TerrainPositions[index].x;
			PositionBuffer[i++] = TerrainPositions[index].y;
			PositionBuffer[i++] = TerrainPositions[index].z;
			index=((z+1)*width)+x;
			PositionBuffer[i++] = TerrainPositions[index].x;
			PositionBuffer[i++] = TerrainPositions[index].y;
			PositionBuffer[i++] = TerrainPositions[index].z;
		}


	i=0;
	for (unsigned int z=0;z<breight-1;z++)
		for (unsigned int x=0;x<width-1;x++)
		{
			//bottom triangle
			index=((z)*width)+(x);
			TextureBuffer[i++] = TerrainTexture[index].x;
			TextureBuffer[i++] = TerrainTexture[index].y;
			index=((z)*width)+(x+1);
			TextureBuffer[i++] = TerrainTexture[index].x;
			TextureBuffer[i++] = TerrainTexture[index].y;
			index=((z+1)*width)+(x+1);
			TextureBuffer[i++] = TerrainTexture[index].x;
			TextureBuffer[i++] = TerrainTexture[index].y;
			//top triangle
			index=((z)*width)+(x);
			TextureBuffer[i++] = TerrainTexture[index].x;
			TextureBuffer[i++] = TerrainTexture[index].y;
			index=((z+1)*width)+(x+1);
			TextureBuffer[i++] = TerrainTexture[index].x;
			TextureBuffer[i++] = TerrainTexture[index].y;
			index=((z+1)*width)+x;
			TextureBuffer[i++] = TerrainTexture[index].x;
			TextureBuffer[i++] = TerrainTexture[index].y;
		}
		
}
