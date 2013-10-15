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



void Terrain::LoadHightMap(SDL_Surface* heightmap)
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

			Uint8 r,g,b;
			GetRGB32(getpixel32(heightmap,x,z),r,g,b);
			float height = r / 256.0f * HeightScale;
			TerrainPositions[index].y=height;

			TerrainPositions[index].x=(float)x * BlockScale;
			TerrainPositions[index].z=(float)z * BlockScale;


			TerrainTexture[index].x = (float) x / (float) width;
			TerrainTexture[index].y = (float) z / (float) breight;


			index++;
		}

	}




    const unsigned int numTriangles = ( width - 1 ) * ( breight - 1 ) * 2;
    int* IndexBuffer = new int [ numTriangles * 3 ];
 
    index = 0;
    for (unsigned int j = 0; j < (breight - 1); ++j )
    {
        for (unsigned int i = 0; i < (width - 1); ++i )
        {
            int vertexIndex = ( j * width ) + i;
            // Top triangle (T0)
            IndexBuffer[index++] = vertexIndex;                    // V0
            IndexBuffer[index++] = vertexIndex + width + 1;        // V3
            IndexBuffer[index++] = vertexIndex + 1;                // V1
            // Bottom triangle (T1)
            IndexBuffer[index++] = vertexIndex;                    // V0
            IndexBuffer[index++] = vertexIndex + width;            // V2
            IndexBuffer[index++] = vertexIndex + width + 1;        // V3
        }
    }



	numVertex = index*4;

	PositionBuffer = new vec3 [numVertex];
	TextureBuffer = new vec2 [numVertex];

	for (unsigned int  i=0;i<index;i++)
	{
		PositionBuffer[i].x = TerrainPositions[IndexBuffer[i]].x;
		PositionBuffer[i].y = TerrainPositions[IndexBuffer[i]].y;
		PositionBuffer[i].z = TerrainPositions[IndexBuffer[i]].z;
	
		TextureBuffer[i].x = TerrainTexture[IndexBuffer[i]].x;
		TextureBuffer[i].y = TerrainTexture[IndexBuffer[i]].y;

	}

	
		
}
