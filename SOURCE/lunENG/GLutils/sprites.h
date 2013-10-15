#pragma once

#include <SDL.h>
#include "shader.h"

class sprites
{
	public:
		
		sprites();
	   ~sprites();


		void drawSprite(int x,int y, SDL_Surface* img);

	private:

		shader* SpriteShader;
};
