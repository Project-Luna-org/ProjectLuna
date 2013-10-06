#pragma once

#include <string>

using namespace std;

class shader
{
public:

	string vsSource;
	string fsSource;
	unsigned int vsID;
	unsigned int fsID;

	unsigned int prog;

	shader(string filenameVertexShader, string filenameFragmentShader); 
   ~shader();

   void useShader();
   void delShader();

};