#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

#ifndef PI
#define PI 3.14159265358979323846
#endif

#define byte unsigned char

string pcharstr(unsigned char* pch);
string constpcharstr(const unsigned char* pch);

double deg2rad(double degree);

float strfloat(string str);
int strnum(string s);

string numstr(int i);
string floatstr(float f);

string GetDigitNumber(int dig);

char* stringchar(string s);

string getPathFromFullFileName(string filename);

void CreateLogFile();

void log(string Text);
void log(int num);


float myrandom();
int randomRange( int low, int high );


wstring s2ws(const string& s);

void error(string thetext);

void makeMessage(string thetext);

void sortUint(unsigned int* &arr);
