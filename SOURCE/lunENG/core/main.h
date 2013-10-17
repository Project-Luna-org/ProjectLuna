/* $Id: main.h 
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
 *		core Folder
 *  <p/> <br/>
 */

/**
 * @file main.h
 *
 * @brief      Some global Variables <p/> <br/>
 * @details    
 */



#pragma once

#include "../GLutils/drawfont.h"
#include "../GLutils/sprites.h"



/**
 * @brief   the current Mouse X position <p/> <br/>
*/
extern int MouseX;

/**
 * @brief   the current Mouse Y position <p/> <br/>
 */
extern int MouseY;



/**
 * @brief   the Time elapsed after the start of the Program <p/> <br/>
 */
extern unsigned int curTimeStamp;




/**
 * @brief   a Standart Font used everythere, initialized at the Startup  <p/> <br/> 
 * @details <p/> <br/> 	Just use this Object to display any Text:  
 * @code
 			aStandartFont->glTextOut(x, y, string, color);
   @endcode
 */
extern drawfont* aStandartFont;

/**
 * @brief   a Standart Sprite-Object used everythere, initialized at the Startup  <p/> <br/>
 * @details <p/> <br/> 	Just use this Object to display any Sprite:  
 * @code
 			aSprite->drawSprite(x, y, SDL_Sprite_Surface);
   @endcode
  */
extern sprites* aSprite;