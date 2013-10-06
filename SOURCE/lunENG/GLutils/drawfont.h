#pragma once
#define NO_SDL_GLEXT

#include <glew.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>

#include "shader.h"

using namespace std;


class drawfont
{
public:

	drawfont(string fontfilename, int size);
   ~drawfont();

	void glTextOut(int x, int y, string txt, Uint32 color);


private:

	
	TTF_Font* curfont;
	GLuint texture;

	shader* FontShader;


	int doround(double x);
	int nextpoweroftwo(float x);


};