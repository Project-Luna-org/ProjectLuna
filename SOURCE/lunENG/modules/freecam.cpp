#define NO_SDL_GLEXT

#include <Windows.h>
#include <glew.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <string>
#include <stdlib.h>
#include <list>
#include <math.h>


#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include <SDL_opengl.h>

#include <glm.hpp>
#include <ext.hpp>


#include "../core/Tools.h"
#include "freecam.h"
#include "../core/main.h"
#include "..\input\keys.h"
#include "../utils/setup.h"


using namespace std;
using namespace glm;

freecam::freecam()
{

	fly=true;

	camX=100;
	camY=10;
	camZ=200;

	camYaw=0;
	camPitch=0;

	keyvel=5;
	
	mousevel=0.02f;


	cameraMatrix = mat4(1);
}

vec3 freecam::getCameraLookAt()
{
	vec3 res;
	float cP = (float) deg2rad(camPitch);
	float cY = (float) deg2rad(camYaw);
	res.x=-cos(cP)*sin(cY);
	res.y=sin(cP);
	res.z=-cos(cP)*cos(cY);
	
	
	res.x+=camX;
	res.y+=camY;
	res.z+=camZ;

	return res;
}


vec3 freecam::getCameraDirection()
{
	vec3 res;
	float cP = (float) deg2rad(camPitch);
	float cY = (float) deg2rad(camYaw);
	res.x=-cos(cP)*sin(cY);
	res.y=sin(cP);
	res.z=-cos(cP)*cos(cY);
	normalize(res);
	return res;
}

void freecam::moveCamera(float dist,float dir)
{
	float rad=(float) deg2rad(camYaw+dir);
	camX-=sin(rad)*dist;
	camZ-=cos(rad)*dist;
}

void freecam::moveCameraUp(float dist,float dir)
{
	float rad=(float) deg2rad(camPitch+dir);
	camY+=sin(rad)*dist;
}


void freecam::CameraControl()
{
		camYaw+=mousevel*(screenwidth / 2 -MouseX);
		camPitch+=mousevel*(screenheight / 2 -MouseY);
	
	if (camPitch>90) camPitch=90;
	if (camPitch<-90) camPitch=-90;
	if (camYaw<0) camYaw+=360;
	if (camYaw>360) camYaw-=360;

	    if (keys::UPpressed)
		{
			if ((camPitch!=90) && (camPitch!=-90))
			{
				moveCamera(keyvel,0);
				if(fly) moveCameraUp(keyvel,0);
			}
		}
		if (keys::DOWNpressed)
		{
			if ((camPitch!=90) && (camPitch!=-90))
			{
				moveCamera(keyvel,180);
                if(fly) moveCameraUp(keyvel,180);
			}
		}
		if (keys::LEFTpressed)
		{
			moveCamera(keyvel,90);
		}
		if (keys::RIGHTpressed)
		{
			moveCamera(keyvel,270);
		}
	
	//glRotatef(-camPitch,1,0,0);
	//glRotatef(-camYaw,0,1,0);
		
		cameraMatrix = rotate(cameraMatrix, -camPitch, vec3(1.0f, 0.0f, 0.0f));
		cameraMatrix = rotate(cameraMatrix, -camYaw, vec3(0.0f, 1.0f, 0.0f));
		
		
	
}


void freecam::CameraTranslate()
{
	cameraMatrix = translate(cameraMatrix,vec3(-camX,-camY, -camZ));
}





vec3 freecam::getCamPos()
{
	return vec3(camX,camY,camZ);
}