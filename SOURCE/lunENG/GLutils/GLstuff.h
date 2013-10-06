#pragma once

#include <string>

using namespace std;



unsigned int loadTexture(string filename);
unsigned int createTexture(int w,int h, bool isDepth=false);

void TraceError();
void CheckFramebufferStatus();



