/* $Id: tools.h 
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
 * @file tools.h
 *
 * @brief      some useful Tools packed into one Module <p/> <br/>
 */



#pragma once

#include <string>

using namespace std;

#ifndef PI
#define PI 3.14159265358979323846
#endif

#define byte unsigned char

/**
 * @brief   convert a char pointer to a string  <p/> <br/>
 */
string pcharstring(char* pch);

/**
 * @brief   convert a unsigned char pointer to a string  <p/> <br/> 
 */
string pcharstr(unsigned char* pch);

/**
 * @brief   convert a constant unsigned char pointer to a string  <p/> <br/> 
 */
string constpcharstr(const unsigned char* pch);

/**
 * @brief   convert a degree to radian  <p/> <br/> 
 */
double deg2rad(double degree);

/**
 * @brief   convert a string to a float value  <p/> <br/> 
 */
float strfloat(string str);

/**
 * @brief   convert a string to an integer value <p/> <br/> 
 */
int strnum(string s);

/**
 * @brief   convert a integer value to a string  <p/> <br/> 
 */
string numstr(int i);

/**
 * @brief   convert a float value to a string  <p/> <br/> 
 */
string floatstr(float f);

/**
 * @brief   if "dig" is below 10 this routine returns a 0 and the digit. above or equal 10 the whole number will be returned  <p/> <br/> 
 * @details <p/> <br/> 	enter 2 will return 02   			
			<br/>		enter 20 will return 20   
			<p/>		very usefull if you have many files sorted by number like 01.bmp, 02.bmp, 03.bmp and so on...
 */
string GetDigitNumber10(int dig);

/**
 * @brief   if "dig" is below 10 this routine returns a 00 and the digit. above or equal 10 and below 100 this routine returns a 0 and the two digits. above or equal 100 the whole number will be returned  <p/> <br/> 
 * @details <p/> <br/> 	enter 2 will return 02   			
			<br/>		enter 20 will return 020   			
			<br/>		enter 200 will return 200   			
			<p/>		very usefull if you have many files sorted by number like 001.bmp, 002.bmp, 003.bmp and so on...
 */
string GetDigitNumber100(int dig);

/**
 * @brief   convert a string to a char pointer <p/> <br/> 
 */
char* stringchar(string s);

/**
 * @brief   extracts the path from a path+filename string without the last slash <p/> <br/> 
 * @details <p/> <br/> 	if you have something like:  C:\\myStuff\\myBin.exe
			<br/>		this function will return: C:\\myStuff
			<p/> <br/>	it accepts unix and windows style slashes

 */
string getPathFromFullFileName(string filename);




/**
 * @brief   creates an empty or clear the existing LOGGER file <p/> <br/> 
 * @details <p/> <br/> 	 it will make a logger.log and write a [LOG] tag in it
 */
void CreateLogFile();

/**
 * @brief   writes a string into the existing LOGGER file <p/> <br/> 
 * @details <p/> <br/> 	 it will make a logger.log if it does not exist, otherwise the logger.log will be created
 */
void log(string Text);


/**
 * @brief   generates a random float value<p/> <br/> 
 */
float floatrandom();

/**
 * @brief   generates a random integer value in the range from low to heigh <p/> <br/> 
 */
int randomRange( int low, int high );


/**
 * @brief   converts a string into a wide string (WINDOWS ONLY) <p/> <br/> 
 */
#ifdef OS_WIN
 wstring s2ws(const string& s);
#endif


/**
 * @brief   a MessageBox with the error message popups and the program terminates emideatly <p/> <br/> 
 */
void error(string thetext);

/**
 * @brief   a MessageBox with a message popups <p/> <br/> 
 */
void makeMessage(string thetext);

/**
 * @brief   retruns the length of a string <p/> <br/> 
 */
unsigned long strlength(string s);


/**
 * @brief   sorts an integer array <p/> <br/> 
 */
void sortUint(unsigned int* &arr);
