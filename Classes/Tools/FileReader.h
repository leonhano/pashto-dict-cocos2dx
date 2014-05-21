// FileReader.h
#ifndef __cocos2d_x_FileReader__	  
#define __cocos2d_x_FileReader__  

#include <vector>
#include "..\DataStruct\WordItem.h"

using namespace std;

class FileReader {
private:
	//ReadFile( string pFileName, char pMode = 'r' );

public:	
	static vector<string> GetStringsFromFile(string pFileName, char pMode = 'r' );
	static vector<CWordItem> GetWordItemsFromFile(string pFileName, char pMode = 'r' );

	static void WriteStringsToFile(string str, string pDestFile, bool isAppend = true);
	static CWordItem* ParseTAGString(string tagString);

	void Sample();
	static vector<string>* split(string work, char delim, int rep) ;
};

#endif

