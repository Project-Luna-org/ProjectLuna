/* $Id: OBJparser.cpp 
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


#include <Windows.h>
#include <gl/GL.h>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <vector>


#include "../core/Tools.h"


#include "OBJparser.h"




using namespace std;



OBJparser::OBJparser(string filename)
{
	vertexCount = 0;
	textureCount = 0;
	normalCount = 0;
	faceCount = 0;

	LoadOBJfile(filename);
}



OBJparser::~OBJparser()
{
	delete [] Faces;
	delete [] Vertices;
	delete [] PositionBuffer;
	delete [] TextureCoordBuffer;
	delete [] NormalsBuffer;
}



string OBJparser::getafloat()
{
	string str="";
	char input='?';
	
	input=theFile[filepos]; filepos++;

	while (input!=' ')
	{
		if (input==10) break;
		if (input==14) break;
		if (input==' ') break;
		str+=input;
		input=theFile[filepos]; filepos++;
	
	}


	return str;
}


string OBJparser::getaint()
{
	string str="";
	char input='?';
	
	input=theFile[filepos]; filepos++;

	while (input!='/')
	{
		if (input==10) break;
		if (input==' ') break;
		if (input==14) break;
		if (input=='/') break;
		str+=input;
		input=theFile[filepos]; filepos++;
	
	}


	return str;
}


bool OBJparser::LoadOBJfile(string filename)
{
	scenename = filename;

	vertexCount = 0;
	textureCount = 0;
	normalCount = 0;
	faceCount = 0;

	ifstream myfile(filename.c_str(),ios::binary);

	
		if(!myfile.good())
		{
			myfile.close();
			error("OBJ: File "+filename+" could not be opened.");
		}

		myfile.seekg(0);
		int filebeginning= (int) myfile.tellg();
		myfile.seekg(0,ios::end);
		int fileending= (int) myfile.tellg();
		myfile.seekg(0);

		filesize=fileending-filebeginning;

		theFile = new char[filesize+1];
		myfile.read(theFile,filesize);

		myfile.close();
		filepos=0;


		char input;
		string s,ss;

	
	
	vector<Vector3f>VerticesList;
	vector<Vector2f>TextcoordsList;
	vector<Vector3f>NormalsList;
	vector<FaceType>FacesList;




	filepos=0;

	// input=theFile[filepos]; filepos++;
	input=' ';
	while(filesize>filepos)
	{
		if(input == 'v')
		{

			input=theFile[filepos]; filepos++;

			// Read in the vertices.
			if(input == ' ') 
			{ 
				Vector3f v;
				ss=getafloat();
				v.x=strfloat(ss);
				ss=getafloat();
				v.y=strfloat(ss);
				ss=getafloat();
				v.z=strfloat(ss) * -1.0f;
				VerticesList.push_back(v);
			}
			
			// Read in the texture uv coordinates.
			if(input == 't') 
			{ 
				input=theFile[filepos]; filepos++;
				if(input == ' ') 
				{ 
					Vector2f v;
					 ss=getafloat();
					 v.u=strfloat(ss);
					 ss=getafloat();
					 v.v=strfloat(ss);
					 TextcoordsList.push_back(v);
				}
			}
			
			// Read in the normals.
			if(input == 'n') 
			{ 
				input=theFile[filepos]; filepos++;
				if(input == ' ') 
				{
					Vector3f v;
					 ss=getafloat();
					 v.x=strfloat(ss);
					 ss=getafloat();
					 v.y=strfloat(ss);
					 ss=getafloat();
					 v.z=strfloat(ss) * -1.0f;
					 NormalsList.push_back(v);
				}
			}
		}

		// Read in the faces.
		if(input == 'f') 
		{
			input=theFile[filepos]; filepos++;
			
			

			if(input == ' ')
			{
				FaceType f;
				ss=getaint();
				f.vIndex3=strnum(ss);
				ss=getaint();
				f.tIndex3=strnum(ss);
				ss=getaint();
				f.nIndex3=strnum(ss);
	
				ss=getaint();
				f.vIndex2=strnum(ss);
				ss=getaint();
				f.tIndex2=strnum(ss);
				ss=getaint();
				f.nIndex2=strnum(ss);

				ss=getaint();
				f.vIndex1=strnum(ss);
				ss=getaint();
				f.tIndex1=strnum(ss);
				ss=getaint();
				f.nIndex1=strnum(ss);

				FacesList.push_back(f);
			}
		}
		
		
		// Start reading the beginning of the next line.
		input=theFile[filepos]; filepos++;

		if (input==14)
		{
			input=theFile[filepos]; filepos++;
		}
		if (input==10)
		{
			input=theFile[filepos]; filepos++;
		}

	}




	vertexCount = VerticesList.size();
	textureCount = TextcoordsList.size();
	normalCount = NormalsList.size();
	faceCount = FacesList.size();



	log(" - file "+filename+" has "+numstr(vertexCount)+"Vertex and "+numstr(faceCount)+"Faces");



		// Initialize the four data structures.
	vertices = new Vector3f[vertexCount];
	if(!vertices) { error("OBJparser.OBJparserfile: create vertex Buffer"); }

	texcoords = new Vector2f[textureCount];
	if(!texcoords) { error("OBJparser.OBJparserfile: create textcoords Buffer"); }

	normals = new Vector3f[normalCount];
	if(!normals)  { error("OBJparser.OBJparserfile: create normals Buffer"); }
	
	faces = new FaceType[faceCount];
	if(!faces)  { error("OBJparser.OBJparserfile: create faces Buffer"); }




	numFaces=faceCount;
	Faces = new Face[numFaces];
	if(!Faces) { error("OBJparser.OBJparserfile: create faces Buffer"); }

	unsigned int vIndex,tIndex,nIndex;



	for(int i=0; i<numFaces; i++)
	{
		vIndex = FacesList[i].vIndex1 - 1;
		tIndex = FacesList[i].tIndex1 - 1;
		nIndex = FacesList[i].nIndex1 - 1;

		Faces[i].x1=VerticesList[vIndex].x; Faces[i].y1=VerticesList[vIndex].y; Faces[i].z1=VerticesList[vIndex].z;
		Faces[i].u1=TextcoordsList[tIndex].u; Faces[i].v1=TextcoordsList[tIndex].v;
		Faces[i].nx1=NormalsList[nIndex].x;Faces[i].ny1=NormalsList[nIndex].y; Faces[i].nz1=NormalsList[nIndex].z;


		vIndex = FacesList[i].vIndex2 - 1;
		tIndex = FacesList[i].tIndex2 - 1;
		nIndex = FacesList[i].nIndex2 - 1;

		Faces[i].x2=VerticesList[vIndex].x; Faces[i].y2=VerticesList[vIndex].y; Faces[i].z2=VerticesList[vIndex].z;
		Faces[i].u2=TextcoordsList[tIndex].u; Faces[i].v2=TextcoordsList[tIndex].v;
		Faces[i].nx2=NormalsList[nIndex].x;Faces[i].ny2=NormalsList[nIndex].y; Faces[i].nz2=NormalsList[nIndex].z;


		vIndex = FacesList[i].vIndex3 - 1;
		tIndex = FacesList[i].tIndex3 - 1;
		nIndex = FacesList[i].nIndex3 - 1;

		Faces[i].x3=VerticesList[vIndex].x; Faces[i].y3=VerticesList[vIndex].y; Faces[i].z3=VerticesList[vIndex].z;
		Faces[i].u3=TextcoordsList[tIndex].u; Faces[i].v3=TextcoordsList[tIndex].v;
		Faces[i].nx3=NormalsList[nIndex].x;Faces[i].ny3=NormalsList[nIndex].y; Faces[i].nz3=NormalsList[nIndex].z;
	}
	


	numVertex = numFaces * 3;
	Vertices = new Vertex[numVertex];

	for(int i=0; i < numFaces; i++)
	{
		Vertices[i * 3 + 0].x = Faces[i].x1;
		Vertices[i * 3 + 0].y = Faces[i].y1;
		Vertices[i * 3 + 0].z = Faces[i].z1;
		Vertices[i * 3 + 0].nx = Faces[i].nx1;
		Vertices[i * 3 + 0].ny = Faces[i].ny1;
		Vertices[i * 3 + 0].nz = Faces[i].nz1;
		Vertices[i * 3 + 0].u = Faces[i].u1;
		Vertices[i * 3 + 0].v = Faces[i].v1;

		Vertices[i * 3 + 1].x = Faces[i].x2;
		Vertices[i * 3 + 1].y = Faces[i].y2;
		Vertices[i * 3 + 1].z = Faces[i].z2;
		Vertices[i * 3 + 1].nx = Faces[i].nx2;
		Vertices[i * 3 + 1].ny = Faces[i].ny2;
		Vertices[i * 3 + 1].nz = Faces[i].nz2;
		Vertices[i * 3 + 1].u = Faces[i].u2;
		Vertices[i * 3 + 1].v = Faces[i].v2;

    	Vertices[i * 3 + 2].x = Faces[i].x3;
		Vertices[i * 3 + 2].y = Faces[i].y3;
		Vertices[i * 3 + 2].z = Faces[i].z3;
		Vertices[i * 3 + 2].nx = Faces[i].nx3;
		Vertices[i * 3 + 2].ny = Faces[i].ny3;
		Vertices[i * 3 + 2].nz = Faces[i].nz3;
		Vertices[i * 3 + 2].u = Faces[i].u3;
		Vertices[i * 3 + 2].v = Faces[i].v3;
	}


	// Release the four data structures.
	if(vertices)
	{
		delete [] vertices;
		vertices = 0;
	}
	if(texcoords)
	{
		delete [] texcoords;
		texcoords = 0;
	}
	if(normals)
	{
		delete [] normals;
		normals = 0;
	}
	if(faces)
	{
		delete [] faces;
		faces = 0;
	}

	
	VerticesList.clear();
	TextcoordsList.clear();
	NormalsList.clear();
	FacesList.clear();





	numPositions=numVertex*3;
	PositionBuffer = new float[numPositions];
	unsigned int index=0;
	for (unsigned int i=0; i<numVertex;i++)
	{
		PositionBuffer[index++] = Vertices[i].x;
		PositionBuffer[index++] = Vertices[i].y;
		PositionBuffer[index++] = Vertices[i].z;
	}

	numTextureCoords=numVertex*2;
	TextureCoordBuffer = new float[numTextureCoords];
	index=0;
	for (unsigned int i=0; i<numVertex;i++)
	{
		TextureCoordBuffer[index++] = Vertices[i].u;
		TextureCoordBuffer[index++] = Vertices[i].v;
	}


	numNormals=numVertex*3;
	NormalsBuffer = new float[numNormals];
	index=0;
	for (unsigned int i=0; i<numVertex;i++)
	{
		NormalsBuffer[index++] = Vertices[i].nx;
		NormalsBuffer[index++] = Vertices[i].ny;
		NormalsBuffer[index++] = Vertices[i].nz;
	}

	return true;
}
