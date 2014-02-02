/* $Id: OBJparser.h 
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
 * @file OBJparser.h
 *
 * @brief      loads a .OBJ file into memory in many ways <p/> <br/> 
 * @details    loads a .OBJ file without a need of a .mtl file <p/> <br/> 
 *			   supports 3 storage methods in the memory: <br/> 
 *			   as Faces <br/> 
 *			   as Vertex <br/> 
 *			   as separate Buffers <br/> 
 *
 */



#pragma once


#include <string>



using namespace std;



/**
 * @brief      loads a .OBJ file into memory in many ways <p/> <br/> 
 * @details    loads a .OBJ file without a need of a .mtl file <p/> <br/> 
 *			   supports 3 storage methods in the memory: <br/> 
 *			   as Faces <br/> 
 *			   as Vertex <br/> 
 *			   as separate Buffers <br/> 
 *
 */
class OBJparser
{
public:

/**
 * @brief      the Face structure. the first way to store the data<p/> <br/> 
 *
 */
	struct Face
	{
		float x1,y1,z1;
		float u1,v1;
		float nx1,ny1,nz1;

		float x2,y2,z2;
		float u2,v2;
		float nx2,ny2,nz2;

		float x3,y3,z3;
		float u3,v3;
		float nx3,ny3,nz3;		
	};


/**
 * @brief      the Face data block <p/> <br/> 
 *
 */
	Face *Faces;

/**
 * @brief      number of Faces stored <p/> <br/> 
 *
 */
	int numFaces;



/**
 * @brief      the Vertex structure. an other way to store the data<p/> <br/> 
 *
 */
	struct Vertex
	{
		float x,y,z;
		float nx,ny,nz;
		float u,v;
	};

/**
 * @brief      the Vertex data block <p/> <br/> 
 *
 */
	Vertex* Vertices;

/**
 * @brief      number of Vertex stored <p/> <br/> 
 *
 */
	unsigned int numVertex;



/**
 * @brief    the Buffer to load in the Renderer (Points)  <p/> <br/> 
 *
 */
	float* PositionBuffer;

/**
 * @brief    the Buffer size to load in the Renderer (Points)  <p/> <br/> 
 *
 */
	unsigned int numPositions;


/**
 * @brief    the Buffer to load in the Renderer (Texture Coordinates)    <p/> <br/> 
 *
 */
	float* TextureCoordBuffer;

/**
 * @brief    the Buffer size to load in the Renderer (Texture Coordinates)    <p/> <br/> 
 *
 */
	unsigned int numTextureCoords;


/**
 * @brief    the Buffer to load in the Renderer (Normals)    <p/> <br/> 
 *
 */
	float* NormalsBuffer;

/**
 * @brief    the Buffer size to load in the Renderer (Normals)    <p/> <br/> 
 *
 */
	unsigned int numNormals;




/**
 * @brief    the name of the scene    <p/> <br/> 
 *
 */
	string scenename;


/**
 * @brief    load a .OBJ file    <p/> <br/> 
 *
 */
	OBJparser(string filename);

/**
 * @brief    clean up    <p/> <br/> 
 *
 */
   ~OBJparser();





private:

	bool LoadOBJfile(string filename);

	struct Vector3f
	{ 
		float x,y,z;
	};
	struct Vector2f
	{
		float u,v;
	};
	struct FaceType
	{
		int vIndex1, vIndex2, vIndex3;
		int tIndex1, tIndex2, tIndex3;
		int nIndex1, nIndex2, nIndex3;
	};

	int vertexCount;
	int textureCount;
	int normalCount;
	int faceCount;


	Vector3f *vertices, *normals;
	Vector2f *texcoords;
	FaceType *faces;


	int filesize;
	int filepos;
	char *theFile;

	string getafloat();
	string getaint();
};
