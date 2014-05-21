#ifndef CSVParse_h__
#define CSVParse_h__

#pragma once
/*!
 * \class CCSVParse
 *
 * \brief 
 *
 * \author Hao
 * \date April 2014
 */

#include <iostream>  
#include "cocos2d.h"  
#include <vector>  

using namespace std;  
USING_NS_CC;  

class CCSVParse  
{  
public:
	static void OutputStrings(const char* fileName, vector<string>* outputStringVector);

protected:  
	//    CCSVParse(void);  
	~CCSVParse(void);  
	CCSVParse(istream& fin=cin, string sep=","):  
		fieldsep(sep),  
		cols(0)  
	{  

	}  

	//用以存储数据  
	std::vector<std::vector<std::string> > data;  
	bool openFile(const char* fileName);  
	const char* getData(unsigned int rows, unsigned int cols);  
	int findColsData(int cols, const char* value);  

	inline int getCols(){return cols;}  
	inline int getRows(){return data.size();}  

private:  
	string        fieldsep;  
	int            cols;  

	void StringSplit(const string& str, vector<string>& tokens, const char& delimiters);  
	void split(vector<string>& field, string line);  
	int advplain(const string& line, string& fld, int);  
	int advquoted(const string& line, string& fld, int);  


};  


#endif // CSVParse_h__
