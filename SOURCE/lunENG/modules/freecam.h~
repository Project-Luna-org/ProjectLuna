/* $Id: freecam.h 
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

/** \dir
 *		modules Folder
 *  <p/> <br/>
 */


/**
 * @file freecam.h
 *
 * @brief      a Spectator Flying Camera <p/> <br/> 
 * @details    you can fly across the whole scene, like in spectator mode<p/> <br/> 
 */

#pragma once

#include <glm.hpp>
#include <ext.hpp>

using namespace glm;




/**
 * @brief      a Spectator Flying Camera  <p/> <br/> 
 *
 */
class freecam
{
public:

/**
 * @brief      setup the Camera start position  <p/> <br/> 
 *
 */
	freecam();

/**
 * @brief      the Keyboard Controller speed <p/> <br/> 
 *
 */
	float keyvel;

/**
 * @brief      the Mouse Controller speed <p/> <br/> 
 *
 */
	float mousevel;


/**
 * @brief      returns the Position Vector <p/> <br/> 
 *
 */

	vec3 getCamPos();

/**
 * @brief      returns the Look At Vector <p/> <br/> 
 *
 */
	vec3 getCameraLookAt();


/**
 * @brief      returns the Direction Vector <p/> <br/> 
 *
 */
	vec3 getCameraDirection();


/**
 * @brief      Setup the Rotation of the Camera by pressing the Arrow-Keys <p/> <br/> 
 * @details    If you make a skybox execute this before drawing the skybox <p/> <br/> 
 *
 */
	void CameraControl();

/**
 * @brief      Move the Camera by Camera Position<p/> <br/> 
 * @details    If you make a skybox execute this after drawing the skybox <p/> <br/> 
 *
 */
	void CameraTranslate();



/**
 * @brief      returns the Matrix to multiply with the World Matrix to apply the Camera translation<p/> <br/> 
 *
 */	
	mat4x4 cameraMatrix;



private:
	
	float camX,camY,camZ;
	float camYaw,camPitch;

	
	void moveCamera(float dist,float dir);
	void moveCameraUp(float dist,float dir);


};



