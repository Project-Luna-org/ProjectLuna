#include "../osSetup.h"

#ifdef OS_WIN
 #include <Windows.h>
#endif
#ifdef OS_OSX
 #include <CoreFoundation/CoreFoundation.h>
#endif

#include <string>
#include <sstream>
#include <stdlib.h>

#include "Tools.h"

using namespace std;




string pcharstr(unsigned char* pch)
{
	if (!pch) return "";
	string s="";
	int i=0;
	char ch='\xFF';
	while(ch!=0)
	{
		ch=pch[i];
		if (ch!=0) s=s+ch;
		i++;
	}
	return s;
}


string constpcharstr(const unsigned char* pch)
{
	if (!pch) return "";
	string s="";
	int i=0;
	char ch='\xFF';
	while(ch!=0)
	{
		ch=pch[i];
		if (ch!=0) s=s+ch;
		i++;
	}
	return s;
}






double deg2rad(double degree)
{
	double radian = 0;
	radian = degree * (PI/180);
	return radian;
}




float strfloat(string str)
{
    char *pch = new char[str.length()];

	unsigned int i=0;
	while (i<str.length())
	{
		pch[i]=str[i];
		i++;
	}
	
	float j;
	j=(float) atof(pch);
	delete[] pch;
	return j;

}

int strnum(string s)
{
	char *pch = new char[s.length()+1];

	unsigned int i=0;
	while (i<s.length())
	{
		pch[i]=s[i];
		i++;
	}
	pch[i]=0;
	int j=0;
	j=atoi(pch);
	delete[] pch;
	return j;
}


string numstr(int i)
{
	stringstream out;
	out << i;

	return out.str();
}

string GetDigitNumber(int dig)
{
	if(dig<10)
	{
		return "0" + numstr(dig); 
	}
	/*
	if((dig>=10) && (dig<100))
	{
		return "0" + numstr(dig);
	}
	*/
	return numstr(dig);

}

string floatstr(float f)
{
	stringstream oss;
	oss << f;
	string str;
	str = oss.str();

	return str;
}



char* stringchar(string s)
{
	unsigned long len=s.length();

	char *c;

	c=new char [len+1];
	
	for (unsigned long i=0;i<s.length();i++)
	{
		c[i]=s[i];
	}

	c[len]=0;

	return c;
}


#ifdef OS_WIN
wstring s2ws(const string& s)
{
    int len;
    int slength = (int)s.length() + 1;
    len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0); 
    wchar_t* buf = new wchar_t[len];
    MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
    wstring r(buf);
    delete[] buf;
    return r;
}
#endif



void CreateLogFile()
{
  filebuf fb;
  fb.open ("logger.log",ios::out);
  ostream os(&fb);
  os << "[LOG]\n";
  fb.close();
}


void log(string Text)
{
  filebuf fb;
  fb.open ("logger.log",std::ios::out|ios::app);
  ostream os(&fb);
  os << Text << "\n";
  fb.close();
}

void log(int num)
{
	log(numstr(num));
}





string getPathFromFullFileName(string filename)
{
	string s=filename;
	unsigned long mycount = s.length();
	char ch=0;

	while (true)
	{
		ch = s[mycount];
		if ((ch=='/') || (ch=='\\')) break;
		mycount--;
	}

	string ss="";
	for (unsigned int i=0;i<mycount;i++)
	{
		ch = s[i];
		ss+=ch;
	}


	return ss;
}

float myrandom()
{
    return rand() / static_cast<float>(RAND_MAX);
}

int randomRange( int low, int high )
{
    int range = high - low;
    return static_cast<int>(myrandom() * range) + low;
}



void error(string thetext)
{
	log("[ERROR] "+thetext);

#ifdef OS_WIN
	wstring stemp = s2ws(thetext);
	LPCWSTR result = stemp.c_str();
	MessageBoxW(NULL,(LPCWSTR) result, L"Error", MB_OK);	
#endif
    
#ifdef OS_OSX
    CFStringRef cfDestination = ::CFStringCreateWithCString(kCFAllocatorDefault, thetext.c_str(),kCFStringEncodingMacRoman);
    
    SInt32 nRes = 0;
    CFUserNotificationRef pDlg = NULL;
    const void* keys[] = { kCFUserNotificationAlertHeaderKey,
        kCFUserNotificationAlertMessageKey };
    const void* vals[] = {
        CFSTR("ERROR"),
        cfDestination
    };
    
    CFDictionaryRef dict = CFDictionaryCreate(0, keys, vals,
                                              sizeof(keys)/sizeof(*keys),
                                              &kCFTypeDictionaryKeyCallBacks,
                                              &kCFTypeDictionaryValueCallBacks);
    
    pDlg = CFUserNotificationCreate(kCFAllocatorDefault, 0,
                                    kCFUserNotificationPlainAlertLevel,
                                    &nRes, dict);
    CFRelease(cfDestination);
    CFRelease(pDlg);
    CFRelease(dict);
#endif
    
	exit(-1);
}




void makeMessage(string thetext)
{
	log("[MESSAGE] "+thetext);
#ifdef OS_WIN
	wstring stemp = s2ws(thetext);
	LPCWSTR result = stemp.c_str();
	MessageBoxW(NULL,(LPCWSTR) result, L"Message", MB_OK);	
#endif
    
#ifdef OS_OSX
    CFStringRef cfDestination = ::CFStringCreateWithCString(kCFAllocatorDefault, thetext.c_str(),kCFStringEncodingMacRoman);
    
    SInt32 nRes = 0;
    CFUserNotificationRef pDlg = NULL;
    const void* keys[] = { kCFUserNotificationAlertHeaderKey,
        kCFUserNotificationAlertMessageKey };
    const void* vals[] = {
        CFSTR("Message Box"),
        cfDestination
    };
    
    CFDictionaryRef dict = CFDictionaryCreate(0, keys, vals,
                                              sizeof(keys)/sizeof(*keys),
                                              &kCFTypeDictionaryKeyCallBacks,
                                              &kCFTypeDictionaryValueCallBacks);
    
    pDlg = CFUserNotificationCreate(kCFAllocatorDefault, 0,
                                    kCFUserNotificationPlainAlertLevel,
                                    &nRes, dict);
    CFRelease(cfDestination);
    CFRelease(pDlg);
    CFRelease(dict);
    
#endif
    
    
}



void sortUint(unsigned int* &arr)
{
	for(int j = 9; j >= 0; j--)
	{
	  for(int i = 0; i < j; i++)
	  {
		if(arr[i] > arr[i + 1])
		{
		  int temp = arr[i + 1];
		  arr[i + 1] = arr[i];
		 arr[i] = temp;
		}
	  }
	}
}




unsigned long strlength(string s)
{
#ifdef OS_OSX
    if (s.length()==0) return 0; else return s.length()-1;
#endif
#ifdef OS_WIN
    return s.length();
#endif
}





