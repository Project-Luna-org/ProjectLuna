/* $Id: freecam.cpp
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
#include "../input/keys.h"
#include "../utils/setup.h"


using namespace std;
using namespace glm;

freecam::freecam()
{

	camX=15;
	camY=215;
	camZ=422;

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
				moveCameraUp(keyvel,0);
			}
		}
		if (keys::DOWNpressed)
		{
			if ((camPitch!=90) && (camPitch!=-90))
			{
				moveCamera(keyvel,180);
                moveCameraUp(keyvel,180);
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