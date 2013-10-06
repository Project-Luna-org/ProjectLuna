

// ver 1.0
// this parser is 
//					CASE SENSITIVE
// and 
//					only for one VALUE per KEYNAME



#pragma once

#include <string>
#include <stdlib.h>
#include <fstream>


using namespace std;


class INIparser
{
public:

	struct Entry
	{
		string keyname;
		string value;
	};

	struct Section
	{
		string SectionName;
		Entry* Entries;
		int numEntries;
	};


	Section* Sections;
	int numSections;

	bool loadINI(string filename);

	string getKeyValue(string section, string keyname);

	void close();

private:

	string LineType(string s);
	string returnSection(string s);
	Entry returnEntry(string s);

};