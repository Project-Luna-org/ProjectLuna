/* $Id: INIparser.h 
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
 * @file INIparser.h
 *
 * @brief	Parse an INI file<p/> <br/>
 * @details    this Parser is CASE SENSITIVE <p/> <br/> 
 *			   only ONE VALUE per KEYNAME supported <p/> <br/> 
 *    		   
 * @todo	   do this non CASE SENSITIVE
 */


#pragma once

#include <string>
#include <stdlib.h>
#include <fstream>


using namespace std;



/**
 * @brief	Parse an INI file<p/> <br/>
 * @details    this Parser is CASE SENSITIVE <p/> <br/> 
 *			   only ONE VALUE per KEYNAME supported <p/> <br/> 
 *    		   
 */
class INIparser
{
public:


/**
 * @brief	   Parse an INI file<p/> <br/>
 *
 */
	INIparser(string filename);


/**
 * @brief	   clean up<p/> <br/>
 *
 */
   ~INIparser();



/**
 * @brief	   get a VALUE by a keyname of a give section<p/> <br/>
 * @details    this Parser is CASE SENSITIVE <p/> <br/> 
 *			   the errors are handeled properly <p/> <br/> 
 *
 */
	string getKeyValue(string section, string keyname);






private:


	INIparser (const INIparser&);
	INIparser& operator=(const INIparser&) const;

	struct Entry
	{
		string keyname;
		string value;
		Entry():keyname(""),value(""){}
	};

	struct Section
	{
		string SectionName;
		Entry* Entries;
		int numEntries;
		Section():SectionName(""), Entries(NULL), numEntries(0){}
	private:
		Section (const Section&);
		Section& operator=(const Section&) const;
	};


	Section* Sections;
	int numSections;

	string LineType(string s);
	string returnSection(string s);
	Entry returnEntry(string s);

};
