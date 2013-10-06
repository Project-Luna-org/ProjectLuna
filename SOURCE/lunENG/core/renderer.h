#pragma once


class renderer
{
public:

	renderer(unsigned int drawingMode,unsigned int PrimitiveType,unsigned int numVertex);
   ~renderer();

	void LoadPoints(void* data, unsigned int numPoints);
	void LoadTextCoords(void* data, unsigned int numUVs);


	void Render(unsigned int shaderProc);

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

};