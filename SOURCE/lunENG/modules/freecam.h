#pragma once

#include <glm.hpp>
#include <ext.hpp>

using namespace glm;

class freecam
{
public:

	bool fly;

	freecam();

	float keyvel;
	float mousevel;

	void moveCamera(float dist,float dir);
	void moveCameraUp(float dist,float dir);

	vec3 getCameraLookAt();
	vec3 getCameraDirection();

	void CameraControl();
	void CameraTranslate();

	

	float camX,camY,camZ;
	float camYaw,camPitch;

	vec3 getCamPos();

	mat4x4 cameraMatrix;

};



