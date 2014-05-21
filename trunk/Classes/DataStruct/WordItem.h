#ifndef __cocos2d_x_CWordItem__  
#define __cocos2d_x_CWordItem__  
#pragma once

#include <vector>
#include <map>
#include <string>

using namespace std;

//word item struct
class CWordItem 
{
public:
	CWordItem(){};
	CWordItem(const string &term, long id);
	CWordItem(const string &term, long id, const string &pronunciation);
	CWordItem(const string &term, long id, const vector<string> &means);
	CWordItem(const string &term, long id, const vector<string> &means, const vector<string> &sampleSentence);
	CWordItem(const string &term, long id, const string &pronunciation, const vector<string> &means, const vector<string> &sampleSentence);

	~CWordItem();
	
	vector<string> ToString();
	string IdToString();
	string TermToString();
	string PronunciationToString();
	vector<string> MeansToString();
	vector<string> SentencesToString();
	
	
	void AddPronunciation(const string &pronunciation);

	/** add mean into meams vector */
	void AddMean(const string &mean);

	/** add sample sentence into sampleSentence vector */
	void AddSentence(const string &sentence);
	 

	string TAGString();
public:
	string m_term;	//key for map; main word
	long m_id;	//main id;

	string m_pronunciation;			//store pronunciation;
	vector<string> m_means;			//store means;
	vector<string> m_sampleSentence;	//store sentences

protected:
	string IdTAGString();

	string IntToString(int i)
	{
		char buffer[64];
		sprintf(buffer, "%d", (int)i);
		return string(buffer);
	}

	string TermTAGString();
	string PronunciationTAGString();
	string MeansTAGString();
	string SentencesTAGString();
};
#endif