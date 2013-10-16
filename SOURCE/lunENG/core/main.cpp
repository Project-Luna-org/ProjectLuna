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

#include "../utils/setup.h"
#include "tools.h"
#include "main.h"
#include "renderer.h"
#include "../utils/SDLgraph.h"
#include "../GLutils/GLstuff.h"
#include "../GLutils/drawfont.h"
#include "../input/keys.h"
#include "../GLutils/sprites.h"
#include "../shared/shared.h"
#include "../modules/freecam.h"
#include "../modules/terrain.h"
#include "../shaderToy.h"


using namespace std;
using namespace glm;



int MouseX=0;
int MouseY=0;

unsigned int curTimeStamp;
drawfont* aStandartFont=NULL;
sprites* aSprite=NULL;



int main(int argc, char** argv)
{

	CreateLogFile();
 
	
	srand((unsigned int) time(NULL));

	GetEngineStartupConfig();
	
	
    if ( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0 ) error("Unable to initialize SDL2: " + (string) SDL_GetError());

 


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

    if(!SDLopenGLcontext)
    {
        const char* errorstr = SDL_GetError();
        error(errorstr);
    }
        

    
	glewExperimental = GL_TRUE;
	GLenum glewError = glewInit(); 
	if( glewError != GLEW_OK ) error("Unable to init GLew: "+constpcharstr(glewGetErrorString(glewError)));
    
	glGetError();

    
    
	const GLubyte* glRenderer = glGetString(GL_RENDERER);
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


	aStandartFont = new drawfont(DATAfolder+"font/arial.ttf",24);
	aSprite = new sprites();
	
	
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
		

	mat4 ProjMatrix = perspective(45.0f, (float) screenwidth / screenheight, 0.1f, 10000.0f);


	//////////////////////////////////////////////////////////////////////////////////////

	
		//	initQuad();

			unsigned int myTerrainTexture = loadTexture(DATAfolder+"graph/terra.jpg");

			SDL_Surface* testIMG;
			testIMG = LoadIMG(DATAfolder+"graph/terra.jpg");

			//SDL_Surface* testNormal=calculateNormalMap(testIMG);


			Terrain* myTerrain = new Terrain(100,4);
			myTerrain->LoadHeightMap(testIMG);
	

			shader* terrainShader;
			if (rendererver == 1)
			 terrainShader = new shader(DATAfolder+"shader/2.1/through.vert", DATAfolder+"shader/2.1/through.frag");
			if (rendererver == 2)
			 terrainShader = new shader(DATAfolder+"shader/3.2/through.vert", DATAfolder+"shader/3.2/through.frag");
			if (rendererver == 3)
			 terrainShader = new shader(DATAfolder+"shader/4.3/through.vert", DATAfolder+"shader/4.3/through.frag");
    
			renderer* terrainRenderer = new renderer(GL_STATIC_DRAW, GL_TRIANGLES,myTerrain->numVertex,terrainShader->prog);

			terrainRenderer->LoadPoints(&myTerrain->PositionBuffer[0],myTerrain->numVertex);
			terrainRenderer->LoadTextCoords(&myTerrain->TextureBuffer[0],myTerrain->numVertex);


			freecam* myCam = new freecam();


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
	progEnterTime=SDL_GetTicks();
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
		
		curTimeStamp=SDL_GetTicks()-progEnterTime;

		// Update





		// Draw
		
		glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



		
	//////////////////////////////////////////////////////////////////////////////////////		
	
	
		
		// drawQuad();
		// aSprite->drawSprite(0,0,testNormal);

			SDL_WarpMouseInWindow(SDLwindow,screenwidth / 2,screenheight / 2);

		glUseProgram(terrainShader->prog);
		glDisable(GL_LIGHTING);



		    glBindTexture( GL_TEXTURE_2D,myTerrainTexture);

		myCam->cameraMatrix = mat4(1);
		myCam->CameraControl();
		myCam->CameraTranslate();


		mat4 matrix = ProjMatrix * myCam->cameraMatrix;
		int matrix_location = glGetUniformLocation (terrainShader->prog, "matrix");
		glUniformMatrix4fv (matrix_location, 1, GL_FALSE, value_ptr(matrix));


		

		terrainRenderer->Render();
		

	//////////////////////////////////////////////////////////////////////////////////////		

		dwFrames++;
		dwCurrentTime = SDL_GetTicks();
		dwElapsedTime = dwCurrentTime - dwLastUpdateTime;
		
		if(dwElapsedTime >= 1000)
		{
			string fps = "fps";
			if (how2showFPS==0 || how2showFPS==1) theFPS = floatstr((float) dwFrames * 1000.0f / dwElapsedTime).append(fps);
			dwFrames = 0;
			dwLastUpdateTime = dwCurrentTime;
		}
		

		

		if (how2showFPS==0) aStandartFont->glTextOut(10, 10 , theFPS, 0xffffffff);
		if (how2showFPS==1) SDL_SetWindowTitle(SDLwindow,stringchar(theFPS));


		SDL_GL_SwapWindow(SDLwindow);
		
	}


	//////////////////////////////////////////////////////////////////////////////////////	

	 //	closeQuad();

	terrainRenderer->~renderer();
	terrainShader->~shader();

	//////////////////////////////////////////////////////////////////////////////////////	





	 aStandartFont->~drawfont();
	 aSprite->~sprites();


	TTF_Quit();
	IMG_Quit();
	SDL_GL_DeleteContext(SDLopenGLcontext);
	SDL_DestroyWindow(SDLwindow);
	SDL_Quit();
	log("normal Exit");
	return 0;
}
