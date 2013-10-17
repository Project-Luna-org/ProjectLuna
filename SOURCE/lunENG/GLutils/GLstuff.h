/* $Id: GLstuff.h 
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
 *		GLutils Folder
 *  <p/> <br/>
 */

/**
 * @file GLstuff.h
 *
 * @brief       some usefull OpenGL-Tools<p/> <br/> 
 */

#pragma once

#include <string>
#include <SDL.h>

using namespace std;


/**
 * @brief   loads a texture from a file up to the graphicscard and returns its index <p/> <br/> 
 */
unsigned int loadTexture(string filename);

/**
 * @brief   loads a empty texture up to the graphicscard and returns its index <p/> <br/> 
 */
unsigned int createTexture(int w,int h);


/**
 * @brief   checks if an OpenGL general error appears, if so execute the error() funktion <p/> <br/> 
 */
void TraceError();

/**
 * @brief   checks if an OpenGL FrameBuffer error appears, if so execute the error() funktion <p/> <br/> 
 */
void CheckFramebufferStatus();



