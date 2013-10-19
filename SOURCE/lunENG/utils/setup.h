/* $Id: setup.h 
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
 *		Utils Folder
 *  <p/> <br/>
 */

/**
 * @file setup.h
 *
 * @brief      Engine Configurations loaded from the engine.ini file<p/> <br/>
 */



#pragma once

#include <string>

using namespace std;


/**
 * @brief   GLSL supporitng version <p/> <br/> 
 * @details	1 -> OpenGL 2.1 <br/> 
 *		    2 -> OpenGL 3.2 <br/> 
 *			3 -> OpenGL 4.3 <br/>  <p/>
 */
extern int rendererver;


/**
 * @brief   the screen width Resolution  <p/> <br/> 
 */
extern int screenwidth;

/**
 * @brief   the screen height Resolution  <p/> <br/> 
 */
extern int screenheight;

/**
 * @brief   swich to fullscreen mode? <p/> <br/> 
 */
extern bool screenFullScreen;


/**
 * @brief   the DATA folder of the project <p/> <br/> 
 * @details	the local path to the DATA/ folder <p/> <br/> 
 */
extern string DATAfolder;


/**
 * @brief   how to display the FPS string <p/> <br/> 
 * @details	0 -> on the screen in the left upper corner <br/> 
 *		    1 -> on the Window Title Bar <br/> 
 *			2 -> not shown <br/>  <p/>
 */
extern int how2showFPS;

/**
 * @brief   do show the mouse cursor? <p/> <br/> 
 */
extern bool showMouse;


/**
 * @brief   where is the executable? <p/> <br/>
 */
extern string absoluteExecutablePath;



/**
 * @brief   Load the Confirutations from the engine.ini file <p/> <br/> 
 */
void GetEngineStartupConfig(string exePath);