

#include <string>
#include <stdlib.h>
#include <fstream>

#include "../core/tools.h"
#include "INIparser.h"

using namespace std;



string INIparser::LineType(string s)
{
	string ss="";
	char ch=0x00;
	unsigned int i=0;


	while (i<s.length())
	{
		ch=s[i];

		if (ch==';') return "comment";

		i++;
	}

	i=0;
	bool emptyline=true;
	while (i<s.length())
	{
		ch=s[i];

		if (ch!=0x0D || ch!=0x0A || ch!=0x00) emptyline=false;

		i++;
	}

	if (emptyline) return "";

	i=0;
	while (i<s.length())
	{
		ch=s[i];

		if (ch=='[') return "section";

		i++;
	}
	
	i=0;
	while (i<s.length())
	{
		ch=s[i];

		if (ch=='=') return "entry";

		i++;
	}
	
	return "unknown";
}


string INIparser::returnSection(string s)
{
	string ss="";
	char ch=0x00;
	unsigned int i=0;
	bool start=false;

	while (i<s.length())
	{
		ch=s[i];

		if (ch==']') start=false;
		if (start) ss+=ch;
		if (ch=='[') start=true;

		i++;
	}
	return ss;
}


INIparser::Entry INIparser::returnEntry(string s)
{
	Entry aEntry;

	unsigned int i=0;
	char ch=0x00;
	while (i<s.length())
	{
		ch=s[i];

		if (ch!=0x0D && ch!=0x0A && ch!=0x00 && ch!=' ' && ch!=0x09) break;

		i++;
	}

	string ss="";

	while (i<s.length())
	{
		ch=s[i];

		if (ch=='=') break;
		ss+=ch;
		i++;
	}

	if (s[i-1]==0x09 || s[i-1]==' ')
	{
		string sss="";
		for (unsigned int ii=0;ii<i-1;ii++)
		{
			sss+=ss[ii];
		}
		ss=sss;
	}

	aEntry.keyname=ss;
	i++;
	ss="";

	while (i<s.length())
	{
		ch=s[i];

		if (ch!=0x0D && ch!=0x0A && ch!=0x00 && ch!=' ' && ch!=0x09) break;

		i++;
	}

	
	while (i<s.length())
	{
		ch=s[i];

		if (ch=='\n') break;
		ss+=ch;
		i++;
	}


	if (s[i-1]==0x09 || s[i-1]==' ')
	{
		string sss="";
		for (unsigned int ii=0;ii<i-1;ii++)
		{
			sss+=ss[ii];
		}
		ss=sss;
	}



	aEntry.value=ss;

	return aEntry;
}

bool INIparser::loadINI(string filename)
{

	ifstream INIfile;

	INIfile.open(filename.c_str());

	if(!INIfile.good())
	{
		// INIfile.close();
		return false;
	}


	string s,ss;


	int MYnumSections=0;


	int linecounter=0;
	while (!INIfile.eof())
	{
		linecounter++;
		getline(INIfile,s);
		ss=LineType(s);

		if (ss!="comment" && ss!="") 
		{

			if (ss=="section")
			{
				MYnumSections++;
			}
			if (ss=="unknown")
			{
				error("INIparser: unknown entry line "+numstr(linecounter));
			}
		}
	}
	INIfile.close();


	numSections=MYnumSections;
	Sections = new Section[numSections];
	
	
	INIfile.open(filename.c_str());

	int curSection=-1;

	int SectionBeginLine=0;

	while (!INIfile.eof())
	{
		linecounter++;
		getline(INIfile,s);
		ss=LineType(s);

		SectionBeginLine++;

		if (ss!="comment" && ss!="") 
		{

			if (ss=="section")
			{

				curSection++;
				Sections[curSection].SectionName = returnSection(s);

				

					int MYnumEntries=0;

					while (!INIfile.eof())
					{
						linecounter++;
						getline(INIfile,s);
						ss=LineType(s);

						if (ss!="comment" && ss!="") 
						{
							if (ss=="section") break;

							
							MYnumEntries++;

						}
					}

				
				Sections[curSection].numEntries = MYnumEntries;
				Sections[curSection].Entries = new Entry[Sections[curSection].numEntries];


					INIfile.close();
					INIfile.open(filename.c_str());
				for (int i=0;i<SectionBeginLine;i++) getline(INIfile,s);
				int curEntry=-1;
				while (!INIfile.eof())
					{
						linecounter++;
						getline(INIfile,s);
						ss=LineType(s);

						if (ss!="comment" && ss!="") 
						{
							if (ss=="section") break;

							curEntry++;
							Sections[curSection].Entries[curEntry] = returnEntry(s);

							// makeMessage(Sections[curSection].Entries[curEntry].keyname+" = "+Sections[curSection].Entries[curEntry].value);



						}
					}

			}
		}
	}


	return true;
}



string INIparser::getKeyValue(string section, string keyname)
{

		string mySection="";
		string myKeyname="";

		for (unsigned int i=0;i<section.length();i++)  mySection+=toupper(section[i]);
		for (unsigned int i=0;i<keyname.length();i++)  myKeyname+=toupper(keyname[i]);
	
	
		string curKeyname="";

		int theSection=-1;
		int theEntry=-1;

		 for(int i=0;i<numSections;i++)
		 {
			 string curSection="";
			 for (unsigned int ii=0;ii<Sections[i].SectionName.length();ii++) curSection+=toupper(Sections[i].SectionName[ii]);
			 if (curSection==mySection) theSection=i;
		 }

		 if (theSection==-1) error("unknown section");
	
	 for(int i=0;i<Sections[theSection].numEntries;i++)
	 {
		 string curKeyname="";
		 for (unsigned int ii=0;ii<Sections[theSection].Entries[i].keyname.length();ii++) curKeyname+=toupper(Sections[theSection].Entries[i].keyname[ii]);
		 if (curKeyname == myKeyname) theEntry=i;
	 }

	 if (theEntry==-1) error("unknown keyname:"+keyname);

	 return Sections[theSection].Entries[theEntry].value;
}



void INIparser::close()
{
	delete [] Sections;
}
