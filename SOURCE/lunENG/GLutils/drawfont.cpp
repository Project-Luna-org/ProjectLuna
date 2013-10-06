#define NO_SDL_GLEXT

#include <Windows.h>
#include <glew.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <string>


#include <SDL.h>
#include <SDL_ttf.h>

#include <glm.hpp>
#include <ext.hpp>

using namespace std;
using namespace glm;


#include "GLstuff.h"
#include "../core/tools.h"
#include "../utils/SDLgraph.h"
#include "../utils/setup.h"
#include "../core/renderer.h"
#include "shader.h"
#include "drawfont.h"





int drawfont::doround(double x)
{
	return (int)(x + 0.5);
}

int drawfont::nextpoweroftwo(float x)
{
	double logbase2 = log(x) / log(2.0f);
	return doround(std::pow(2,ceil(logbase2)));
}

void drawfont::glTextOut(int x, int y, string txt, Uint32 color)
{

	if (!curfont) error("glTextOut: font is not initialized!");

	SDL_Color tmpfontcolor;
    Uint8 r,g,b;

    r=0;
    g=0;
    b=0;
    
	GetRGB32(color,r,g,b);

    
    tmpfontcolor.r = r;
    tmpfontcolor.g = g;
    tmpfontcolor.b = b;


	SDL_Surface *resulting_text;
    
    resulting_text = TTF_RenderText_Blended(curfont, txt.data(), tmpfontcolor);
	if (!resulting_text) error("glTextOut: TTF_RenderText_Blended fails: "+ (string) SDL_GetError());


	int w = resulting_text->w;
	int h = resulting_text->h;


	SDL_Surface* intermediary = SDL_CreateRGBSurface(0, w, h, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);

	if (!intermediary) error("glTextOut: SDL_CreateRGBSurface fails: "+ (string) SDL_GetError());

	SDL_BlitSurface(resulting_text, 0, intermediary, 0);

	SDL_FreeSurface(resulting_text);


	
	
        glGenTextures( 1, &texture );
			
		
		glBlendFunc(GL_ONE, GL_ONE);
		glEnable(GL_BLEND);
		
		
    
        glBindTexture( GL_TEXTURE_2D, texture );
        

		

        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
        
		
		

		
        glTexImage2D( GL_TEXTURE_2D, 0,GL_RGBA, intermediary->w, intermediary->h, 0, 
                      GL_BGRA, GL_UNSIGNED_BYTE, intermediary->pixels );


        SDL_FreeSurface( intermediary );
	
 


	float v[] = {
					(float) x+0, (float) y+0, 0,			
					(float) x+w, (float) y+0, 0,
					(float) x+w, (float) y+h, 0,
					(float) x+0, (float) y+h, 0
				};	



	float t[] = {
					0,0,
					1,0,
					1,1,
					0,1
				};

         

	/*
		unsigned int PointsVBO = 0;
		unsigned int UVsVBO = 0;

		

		glGenBuffers (1, &PointsVBO);
		glBindBuffer (GL_ARRAY_BUFFER, PointsVBO);
		glBufferData (GL_ARRAY_BUFFER,  12 * sizeof (float), &v, GL_STATIC_DRAW);


		glGenBuffers (1, &UVsVBO);
		glBindBuffer (GL_ARRAY_BUFFER, UVsVBO);
		glBufferData (GL_ARRAY_BUFFER,  8 * sizeof (float), &t, GL_STATIC_DRAW);
		
		
		

		unsigned int vao = 0;
		glGenVertexArrays (1, &vao);
		glBindVertexArray (vao);
		glEnableVertexAttribArray (0);
		glBindBuffer (GL_ARRAY_BUFFER, PointsVBO);
		glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);

		glEnableVertexAttribArray (1);
		glBindBuffer (GL_ARRAY_BUFFER, UVsVBO);
		glVertexAttribPointer (1, 2, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);

		*/


	

	renderer* fontrenderer =  new renderer(GL_STREAM_DRAW,GL_TRIANGLE_FAN,4); 

	fontrenderer->LoadPoints(v,12);
	fontrenderer->LoadTextCoords(t,8);



	glUseProgram(FontShader->prog);

	


		mat4 ProjMatrix = mat4(1);
		ProjMatrix = ortho<float>(0.0f, (float) screenwidth, (float) screenheight, 0, -1.0f, 1.0f);


		mat4 matrix = ProjMatrix;
		int matrix_location = glGetUniformLocation (FontShader->prog, "matrix");
		glUniformMatrix4fv (matrix_location, 1, GL_FALSE, value_ptr(matrix));


		
		/*
	glBindVertexArray (vao);
	glDrawArrays (GL_TRIANGLE_FAN, 0, 4);
	*/




	fontrenderer->Render(FontShader->prog);



	




	glUseProgram(0);

	glDisable(GL_BLEND);
	glDeleteTextures( 1, &texture );


	fontrenderer->~renderer();


	/*
	glDeleteVertexArrays(1,&vao);

	glDeleteBuffers(1,&PointsVBO);
	glDeleteBuffers(1,&UVsVBO);
	*/


	
}


drawfont::drawfont(string fontfilename,int size)
{
		
	if (!(curfont = TTF_OpenFont(stringchar(fontfilename), size))) error("TTF_OpenFont "+fontfilename+" fails: " + (string) SDL_GetError());

	FontShader = new shader(DATAfolder+"shader/font.vert", DATAfolder+"shader/font.frag");


}

drawfont::~drawfont()
{
	TTF_CloseFont(curfont);
	FontShader->~shader();
}
