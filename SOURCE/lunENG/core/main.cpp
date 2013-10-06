#define NO_SDL_GLEXT

#include <Windows.h>
#include <glew.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <string>
#include <stdlib.h>
#include <time.h>

#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <glm.hpp>
#include <ext.hpp>

#include "../utils/setup.h"
#include "tools.h"
#include "main.h"
#include "../GLutils/drawfont.h"
#include "../input/keys.h"

#include "../shaderToy.h"


using namespace std;
using namespace glm;



int MouseX=0;
int MouseY=0;

unsigned int curTimeStamp;
drawfont* exStandartFont=NULL;



int main(int argc, char** argv)
{

	CreateLogFile();
	
	srand((unsigned int) time(NULL));

	GetEngineStartupConfig();
	
	
    if ( SDL_Init(SDL_INIT_VIDEO) != 0 ) error("Unable to initialize SDL2: " + (string) SDL_GetError());



	if (rendererver == 1)
	{
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,2);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,1);
	} else 
	if (rendererver == 2)
	{
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,2);
	} else 
	if (rendererver == 3)
	{
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,3);
	} else error("renderer version in engine.ini is corrrupt");

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	//SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);


	

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	
	SDL_Window *SDLwindow = NULL;
	unsigned int WindowFlags;

	if (screenFullScreen) WindowFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN; else WindowFlags = SDL_WINDOW_OPENGL;

	SDLwindow = SDL_CreateWindow("lunENG 1.0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenwidth,screenheight, WindowFlags);
	if (!SDLwindow) error("SDL_CreateWindow: "+ (string) SDL_GetError());

	
    SDL_GLContext SDLopenGLcontext = SDL_GL_CreateContext(SDLwindow);
	

	glewExperimental = GL_TRUE;
	GLenum glewError = glewInit(); 
	if( glewError != GLEW_OK ) error("Unable to init GLew: "+constpcharstr(glewGetErrorString(glewError)));
	glGetError();


	const GLubyte* glRenderer = glGetString (GL_RENDERER); 
	const GLubyte *glVersion= glGetString(GL_VERSION);
	log("OpenGL renderer "+pcharstr((unsigned char*)glRenderer));
	log("OpenGL version "+pcharstr((unsigned char*)glVersion));

		
    GLint major,minor;
    glGetIntegerv(GL_MAJOR_VERSION, &major);
    glGetIntegerv(GL_MINOR_VERSION, &minor);

	//if (major<3) error("OpenGL version 3.3 not supported");
	//if (minor<3) error("OpenGL version 3.3 not supported");

	
	
	int flags=IMG_INIT_JPG | IMG_INIT_PNG;
	int initted=IMG_Init(flags);
	if((initted & flags) != flags) error("Unable to initialize SDL2_Image: "+ (string) SDL_GetError());



	if (TTF_Init() < 0) error("TTF_Init fails: " + (string) SDL_GetError());  


	exStandartFont = new drawfont(DATAfolder+"font/arial.ttf",24);
	
	
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
		

	mat4 ProjMatrix = perspective(45.0f, (float) screenwidth / screenheight, 0.1f, 1000.0f);


	//////////////////////////////////////////////////////////////////////////////////////

	
			initQuad();
	
	//////////////////////////////////////////////////////////////////////////////////////


	SDL_ShowCursor(showMouse);

	unsigned int dwFrames = 0;
	unsigned int dwCurrentTime = 0;
	unsigned int dwLastUpdateTime = 0;
	unsigned int dwElapsedTime = 0;
	string theFPS="";
	unsigned int progEnterTime=0;

	bool quit=false;
	SDL_Event event;
	progEnterTime=GetTickCount();
	while (!quit)
	{

		//Event polling
		while (SDL_PollEvent(&event))
		{
			switch(event.type) 
			{
				case SDL_MOUSEMOTION:
				{
					MouseX=event.motion.x;
					MouseY=event.motion.y;
				} break;
				case SDL_QUIT: { quit = true; } break;
				case SDL_APP_TERMINATING: { quit = true; } break;
				case SDL_WINDOWEVENT_CLOSE: { quit=true; } break;
				case SDL_KEYDOWN: 
					{
						switch (event.key.keysym.sym)
						{
							case SDLK_ESCAPE: {quit = true;} break;
							case SDLK_RIGHT: { keys::RIGHTpressed = true;} break;
							case SDLK_LEFT: { keys::LEFTpressed = true; } break;	
							case SDLK_UP: { keys::UPpressed = true; } break;	
							case SDLK_DOWN: { keys::DOWNpressed = true; } break;	
							case SDLK_SPACE: { keys::SPACEpressed = true; } break;	
							default: break;
						}
					} break;
				case SDL_KEYUP: 
					{
						switch (event.key.keysym.sym)
						{
							case SDLK_RIGHT: { keys::RIGHTpressed = false;} break;
							case SDLK_LEFT: { keys::LEFTpressed = false; } break;	
							case SDLK_UP: { keys::UPpressed = false; } break;	
							case SDLK_DOWN: { keys::DOWNpressed = false; } break;	
							case SDLK_SPACE: { keys::SPACEpressed = false; } break;	
							default: break;
						}
					} break;
				default: break;
			}
		}
		
		curTimeStamp=GetTickCount()-progEnterTime;

		// Update





		// Draw
		
		glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



		
	//////////////////////////////////////////////////////////////////////////////////////		
	
	
		
		drawQuad();
		


	//////////////////////////////////////////////////////////////////////////////////////		

		dwFrames++;
		dwCurrentTime = GetTickCount(); 
		dwElapsedTime = dwCurrentTime - dwLastUpdateTime;
		
		if(dwElapsedTime >= 1000)
		{
			string fps = "fps";
			if (how2showFPS==0 || how2showFPS==1) theFPS = floatstr((float) dwFrames * 1000.0f / dwElapsedTime).append(fps);
			dwFrames = 0;
			dwLastUpdateTime = dwCurrentTime;
		}
		

		

		if (how2showFPS==0) exStandartFont->glTextOut(10, 10 , theFPS, 0xffffffff);
		if (how2showFPS==1) SDL_SetWindowTitle(SDLwindow,stringchar(theFPS));


		SDL_GL_SwapWindow(SDLwindow);
		
	}


	//////////////////////////////////////////////////////////////////////////////////////	

		closeQuad();


	//////////////////////////////////////////////////////////////////////////////////////	





	 exStandartFont->~drawfont();


	TTF_Quit();
	IMG_Quit();
	SDL_GL_DeleteContext(SDLopenGLcontext);
	SDL_DestroyWindow(SDLwindow);
	SDL_Quit();
	log("normal Exit");
	return 0;
}
