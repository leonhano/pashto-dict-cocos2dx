#ifndef __cocos2d_x___CWordManager_H__
#define __cocos2d_x___CWordManager_H__

#pragma once

#include "WordItem.h"

//word Manager to add word
class CWordManager 
{
public:
	static CWordManager &getInstance()
	{
		static CWordManager instance;
		return instance;
	}
	
	/** add words */
	void AddWord(CWordItem* pWordItem);	
	void AddWord(const string &term, long id, const string &pronunciation);
	void AddWord(const string &term, long id, const string &pronunciation, const vector<string> &means);
	void AddWord(const string &term, long id, const vector<string> & means, const vector<string> & sentences);
	void AddWord(const string &term, long id, const string &pronunciation, const vector<string> & means, const vector<string> & sentences);
	
	//void AddWord(const string &term, long id, string pronunciation="", vector<string> & means=vector<string>(), vector<string> & sentences=vector<string>());
	
	vector<CWordItem>* GetWords(const string &word);

	/** insert means */
	//void InsertMean(const string &word, const string &mean);
	
	/** insert sentence */
	//void InsertSentence(const string &word, const string &sentence);
private:
	CWordManager(){};
	// don't forget to declare these two. You want to make sure they
	// are unaccessible otherwise you may accidentally get copies of
	// your singleton appearing.
	CWordManager(CWordManager const&);		// Don't implement
	void operator=(CWordManager const&);	// Don't implement

public:
	map<string, vector<CWordItem> > m_wordsMap;
	
	void CreateWordsMapFromFile(const char* fileName);

protected:
	enum empties_type { empties_ok, no_empties };   		
	vector<string>& split(vector<string>& result, const string& s, const string& delimiters, empties_type empties/* = SplitType::empties_ok */);

	CWordItem* ParseVectorString(vector<string>& data);
};
#endif