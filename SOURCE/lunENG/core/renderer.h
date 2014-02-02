/* $Id: renderer.h 
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
 * @file renderer.h
 *
 * @brief      manages the rendering depends on the GLSL version <p/> <br/> 
 * @details    loads and renders a VertexBuffer <p/> <br/> 
 *			   if the Texture coordinates are seted it will render with the Texture Coordinates Buffer <p/> <br/> 
 *    		   
 * @todo	   implement index buffer		
 */



#pragma once



/**
 * @brief      manages the rendering depends on the GLSL version (the renderver variable) <p/> <br/> 
 * @details    loads and renders a VertexBuffer with a custom Primitive Type and Draw Mode. <p/> <br/> 
 *			   requers seted shader Program and Vertex count to render <p/> <br/> 
 *    		   
 */
class renderer
{
public:


/**
 * @brief      setups the Drawing Mode, the Primetive Type and the Shader Program <p/> <br/> 
 *
 * @param      drawingMode     can be GL_STREAM_DRAW or GL_STATIC_DRAW <p/> <br/> 
 * @param      PrimitiveType   can be GL_TRIANLGES or GL_TRIANGLE_FAN​ or GL_TRIANGLE_STRIP​ or GL_POINTS​ or GL_LINES​ or GL_LINE_LOOP​ or GL_LINE_STRIP​ <p/> <br/> 
 * @param      shaderProc      must be the shader program which manages the display output <p/> <br/> 
 *
 */
	renderer(unsigned int drawingMode,unsigned int PrimitiveType, unsigned int shaderProc);

/**
 * @brief      clean up <p/> <br/> 
 *
 */
   ~renderer();

/**
 * @brief      set the number of Vertex will be drawn with the Render() function, depends on the Primetive Type <p/> <br/> 
 *
 */
    void setNumVertex(unsigned int numVertex);


/**
 * @brief      passes a float array and number of floats (one float for X, Y and Z) to the VertexBuffer of the renderer <p/> <br/> 
 *
 * @param      data			an array of vertex data <p/> <br/> 
 * @param      numPoints	number of floats (one float for X, Y and Z). If you have one vertex pass 3 here <p/> <br/> 
 *
 */
    void LoadPoints(void* data, unsigned int numPoints);

/**
 * @brief      passes a float array and number of floats (one float for U, V ) to the TextureCoordinateBuffer of the renderer <p/> <br/> 
 *
 * @param      data		an array of texture coordinate data <p/> <br/> 
 * @param      numUVs	number of floats (one float for U, V). If you have one texture coordinate pass 2 here <p/> <br/> 
 *
 */
	void LoadTextCoords(void* data, unsigned int numUVs);



/**
 * @brief      renders the data in the Buffers depends on the GLSL version<p/> <br/> 
 * @details    you must mannualy setup the shader program, the material and the matrix<p/> <br/> 
 *			   this function renders only the earlier given Buffers depends on the GLSL version (renderver variable)<p/> <br/> 
 *    		   
 */
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
	
	unsigned int shaderProc;

	unsigned int numVertex;
    
	int loc_inVertex;
    	int loc_inTextCoords;
    
    	unsigned int VAO;
    
};
