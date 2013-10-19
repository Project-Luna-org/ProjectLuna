/* $Id: setup.cpp
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


#include <string>
#include "../core/tools.h"
#include "setup.h"
#include  "INIparser.h"

using namespace std;

int rendererver=0;
string DATAfolder="../data/";
int screenwidth=1280;
int screenheight=720;
bool screenFullScreen=false;
int how2showFPS=0;
bool showMouse = true;
string absoluteExecutablePath="";


void GetEngineStartupConfig(string exePath)
{
    
    
	INIparser* myINI = new INIparser(exePath+"/engine.ini");


	rendererver = strnum(myINI->getKeyValue("CORE","renderer"));

	screenwidth = strnum(myINI->getKeyValue("CORE","width"));
	
	string s = myINI->getKeyValue("CORE","height");
	screenheight = strnum(s);

	if (myINI->getKeyValue("CORE","fullscreen")=="true")
	{
		screenFullScreen = true;
	} else if (myINI->getKeyValue("CORE","fullscreen")=="false")
	{
		screenFullScreen = false;
	} else error("engine.ini: corrupt 'fullscreen' TAG !");

	if (myINI->getKeyValue("CORE","showMouse")=="true")
	{
		showMouse = true;
	} else if (myINI->getKeyValue("CORE","showMouse")=="false")
	{
		showMouse=false;
	} else error("engine.ini: corrupt 'showMouse' TAG !");

	DATAfolder = exePath+"/"+myINI->getKeyValue("CORE","datapath");
	
	if (myINI->getKeyValue("CORE","showFPS")=="onScreen")
	{
		how2showFPS=0;
	} else if (myINI->getKeyValue("CORE","showFPS")=="onWindowBar")
	{
		how2showFPS=1;
	} else if (myINI->getKeyValue("CORE","showFPS")=="off")
	{
		how2showFPS=2;
	} else error("engine.ini: corrupt 'showFPS' TAG ! ->"+myINI->getKeyValue("CORE","showFPS")+"?");


	myINI->~INIparser();
}

