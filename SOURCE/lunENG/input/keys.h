/* $Id: keys.h 
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


/**
 * @file keys.h
 *
 * @brief      stores keyboard status <p/> <br/> 
 * @details    stores some keys status as a static variables in the class<p/> <br/> 
 */


#pragma once

/**
 * @brief      stores keyboard status <p/> <br/> 
 *
 */
class keys
{
public:

/**
 * @brief      returns true if the UP-arrow-key is pressed <p/> <br/> 
 * 
 */
	static bool UPpressed;

/**
 * @brief      returns true if the DOWN-arrow-key is pressed <p/> <br/> 
 * 
 */
	static bool DOWNpressed;

/**
 * @brief      returns true if the LEFT-arrow-key is pressed <p/> <br/> 
 * 
 */
	static bool LEFTpressed;

/**
 * @brief      returns true if the RIGHT-arrow-key is pressed <p/> <br/> 
 * 
 */
	static bool RIGHTpressed;

/**
 * @brief      returns true if the SPACE-key is pressed <p/> <br/> 
 * 
 */
	static bool SPACEpressed;

};