#pragma once


class renderer
{
public:

	renderer(unsigned int drawingMode,unsigned int PrimitiveType,unsigned int numVertex, unsigned int shaderProc);
   ~renderer();

	void LoadPoints(void* data, unsigned int numPoints);
	void LoadTextCoords(void* data, unsigned int numUVs);


	void Render();

private:
			
	
	unsigned int PointsVBO;
	unsigned int numPoints;
	int attributePoints;

	unsigned int UVsVBO;
	unsigned int numUVs;
	int attributeUVs;

	unsigned int drawingMode;
	unsigned int PrimitiveType;
	unsigned int numVertex;

    unsigned int shaderProc;
    
    int loc_inVertex;
    int loc_inTextCoords;
    
    unsigned int VAO;
    
};