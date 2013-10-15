#pragma once

#include <string>
#include <SDL.h>

using namespace std;



unsigned int loadTexture(string filename);
unsigned int createTexture(int w,int h, bool isDepth=false);

void TraceError();
void CheckFramebufferStatus();



