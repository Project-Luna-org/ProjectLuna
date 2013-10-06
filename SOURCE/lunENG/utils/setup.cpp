

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



void GetEngineStartupConfig()
{
	INIparser myINI;
	if (!myINI.loadINI("engine.ini")) error("Unable to load 'engine.ini' !");


	rendererver = strnum(myINI.getKeyValue("CORE","renderer"));

	screenwidth = strnum(myINI.getKeyValue("CORE","width"));
	
	string s = myINI.getKeyValue("CORE","height");
	screenheight = strnum(s);

	if (myINI.getKeyValue("CORE","fullscreen")=="true")
	{
		screenFullScreen = true;
	} else if (myINI.getKeyValue("CORE","fullscreen")=="false")
	{
		screenFullScreen = false;
	} else error("engine.ini: corrupt 'fullscreen' TAG !");

	if (myINI.getKeyValue("CORE","showMouse")=="true")
	{
		showMouse = true;
	} else if (myINI.getKeyValue("CORE","showMouse")=="false")
	{
		showMouse=false;
	} else error("engine.ini: corrupt 'showMouse' TAG !");

	DATAfolder = myINI.getKeyValue("CORE","datapath");
	
	if (myINI.getKeyValue("CORE","showFPS")=="onScreen")
	{
		how2showFPS=0;
	} else if (myINI.getKeyValue("CORE","showFPS")=="onWindowBar")
	{
		how2showFPS=1;
	} else if (myINI.getKeyValue("CORE","showFPS")=="off")
	{
		how2showFPS=2;
	} else error("engine.ini: corrupt 'showFPS' TAG ! ->"+myINI.getKeyValue("CORE","showFPS")+"?");


	myINI.close();
}

