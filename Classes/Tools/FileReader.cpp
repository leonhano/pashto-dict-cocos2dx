// FileReader.cpp
#include "FileReader.h"
#include <fstream>

#include "cocos2d.h"

USING_NS_CC;

//get string vector from file;
vector<string>	FileReader::GetStringsFromFile(string pFileName, char pMode )
{
	vector<string> fileContents;
	// Create input file stream
	ifstream inputStream;
	string thisLine;

	// Open file
	//inputStream.open(pFileName);
	string fullpath =CCFileUtils::sharedFileUtils()->fullPathForFilename(pFileName.c_str()); 
	inputStream.open(fullpath.c_str());

	// Check if it is open
	if ( !inputStream.is_open( ) ) {
		CCLog("[ ERROR ] Cannot open file: %s " , fullpath.c_str());
		exit( 1 );
	}

	while ( getline( inputStream, thisLine ) ) {
		// Put all lines in vector
		fileContents.push_back( thisLine );
	}

	inputStream.close( );
	CCLog("[ NOTICE ] Finished opening file: %s " , fullpath.c_str());
	return fileContents;
}

//get WordItems (vector) from file
vector<CWordItem> FileReader::GetWordItemsFromFile(string pFileName, char pMode)
{
	vector<CWordItem> fileContents;

	/*
	//for windows only
	// Create input file stream
	ifstream inputStream;
	string thisLine;

	// Open file
	//inputStream.open(pFileName);
	string fullpath =CCFileUtils::sharedFileUtils()->fullPathForFilename(pFileName.c_str()); 
	inputStream.open(fullpath.c_str());

	// Check if it is open
	if ( !inputStream.is_open( ) ) {
		CCLog("[ ERROR ] Cannot open file:  %s " , fullpath.c_str());
		exit( 1 );
	}

	//read data lines by lines;
	while ( getline( inputStream, thisLine ) ) {

		ParseTAGString(thisLine);
		//string pch = strtok(strdup(thisLine.c_str())," |$| ");
		//fileContents.push_back( thisLine );
	}

	inputStream.close( );

	CCLog("[ NOTICE ] Finished opening file: %s ", fullpath.c_str( ));
	*/

	//work for all platform;
	unsigned long max_length;
	unsigned const char* data = CCFileUtils::sharedFileUtils()->getFileData(pFileName.c_str(), "r", &max_length);
	
	CCLog("[ NOTICE ] Finished opening file: %s ", data);
	CCLog("[ NOTICE ] done!!");

	CCString* pRet = CCString::createWithData(data, max_length);

	ParseTAGString(pRet->m_sString);

	return fileContents;
}

//write string to file;
void FileReader::WriteStringsToFile(string str, string pDestFile, bool isAppend)
{
	/*
	//for windows only
	ofstream outFileStream;
	string fullpath =CCFileUtils::sharedFileUtils()->fullPathForFilename(pDestFile.c_str()); 
	if(isAppend)
		outFileStream.open(fullpath.c_str(),  std::fstream::in | std::fstream::out | std::fstream::app);
	else
		outFileStream.open(fullpath.c_str(),  std::fstream::in | std::fstream::out);


	if(outFileStream.is_open())
	{
		outFileStream << str << "\n";
		CCLog("write string  to file: %s", str.c_str());
		outFileStream.close();
	}
	else
	{
		CCLog("Error! Unable to open file : %s", fullpath.c_str());
	}	
	*/
}

CWordItem* FileReader::ParseTAGString(string tagString)
{
	//tagString = "اباتول	Ābātawul 	To build, To construct.	To cultivate, To render habitable or populous.	To fatten	To settle		";
	//string token = "	";
	
	vector<string> output = *split(tagString, ' 	', 0);
	for(vector<string>::iterator it = output.begin(); it != output.end(); it++)
	{
		string splitOut = *it;
		CCLog(splitOut.c_str());
	}
	return NULL;
}

void FileReader::Sample()
{
	unsigned char* pBuffer = NULL;
	unsigned long bufferSize = 0;
	//pBuffer = cocos2d::CCFileUtils::getFileData(fullpath, "r", &bufferSize);
	pBuffer = CCFileUtils::sharedFileUtils()->getFileData("Sourcedate.txt", "r", &bufferSize);
	CCLog("%ld",bufferSize);
	
	for (int i = 0; i < bufferSize; ++i) 
	{
	    CCLog("%c",pBuffer[i]);
	}
	
	CCString* pRet = CCString::createWithData(pBuffer, bufferSize);
	const char* MyBuffer = pRet->getCString();
	CCLog(MyBuffer);
	if (pBuffer)
	{
		delete [] pBuffer;
		pBuffer = NULL;
	} 
}

// split: receives a char delimiter; returns a vector of strings
// By default ignores repeated delimiters, unless argument rep == 1.
vector<string>* FileReader::split(string work, char delim, int rep) {

	vector<string>* flds = new vector<string>();
	string buf = "";
	int i = 0;
	while (i < work.length()) {
		if (work[i] != delim)
			buf += work[i];
		else if (rep == 1) {
			flds->push_back(buf);
			buf = "";
		} else if (buf.length() > 0) {
			flds->push_back(buf);
			buf = "";
		}
		i++;
	}
	if (!buf.empty())
		flds->push_back(buf);
	return flds;
}