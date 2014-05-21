#include "WordManager.h"
#include "Tools\CSVParse.h"
#include "Tools\FileReader.h"

using namespace std;

void CWordManager::AddWord(CWordItem* pWordItem)
{
	if(pWordItem == NULL)
		return;

	string term = pWordItem->m_term;
	map<string, vector<CWordItem> >::iterator it = m_wordsMap.find(term);
	if(it != m_wordsMap.end())
	{	
		it->second.push_back(*pWordItem);
	}
	else
	{
		vector<CWordItem> wordsVector;
		wordsVector.push_back(*pWordItem);
		m_wordsMap.insert(make_pair(term, wordsVector));		
	}
}
void CWordManager::AddWord(const string &term, long id, const string &pronunciation)
{
	AddWord(term, id, pronunciation, vector<string>(), vector<string>());
}

void CWordManager::AddWord(const string &term, long id, const string &pronunciation, const vector<string> &means)
{
	AddWord(term, id, pronunciation, means, vector<string>());
}

void CWordManager::AddWord(const string &term, long id, const vector<string> & means, const vector<string> & sentences)
{
	AddWord(term, id, "", means, sentences);
}
void CWordManager::AddWord(const string &term, long id, const string &pronunciation, const vector<string> & means, const vector<string> & sentences)
{
	CWordItem wordItem(term, id, pronunciation, means, sentences);
	AddWord(&wordItem);
}

vector<CWordItem>* CWordManager::GetWords(const string &term)
{
	map<string, vector<CWordItem> >::iterator it = m_wordsMap.find(term);

	if(it != m_wordsMap.end())
	{		
		return &(it->second);
	}	

	else
		return NULL;
}
/*
void CWordManager::InsertMean(const string &term, const string &mean)
{
	CWordItem *pWordItem = GetWords(term);
	if(pWordItem)
	{
		pWordItem->AddMean(mean);
	}
	else
	{
		//no element, then add a new one;
		throw(ERROR_CAN_NOT_COMPLETE);
	}
}

void CWordManager::InsertSentence(const string &term, const string &sentence)
{
	CWordItem *pWordItem = GetWord(term);
	if(pWordItem)
	{
		pWordItem->AddSentence(sentence);
	}
	else
	{
		//no element, then add a new one;
		throw(ERROR_CAN_NOT_COMPLETE);
	}

}
*/

//create words map from file;
void CWordManager::CreateWordsMapFromFile(const char* fileName)
{
	//reading csv file;
	vector<string> pashtoData1;
	CCSVParse::OutputStrings(fileName, &pashtoData1);

	for(vector<string>::iterator it = pashtoData1.begin(); it != pashtoData1.end(); it++)
	{
		string src = *it;
		vector <string> fields;
		split(fields, *it, ",", empties_ok);
		CWordItem* wordItem = ParseVectorString(fields);
		if(wordItem == NULL)
		{
			CCLog("Error! src data can't be parsed!   src :  %s   ", src.c_str());
		}
		else
		{
			AddWord(wordItem);
		}
	}

	CCLog("Success!  %d words had been added into map", m_wordsMap.size());
}

//split string 
vector<string>& CWordManager::split(vector<string>& result, const string& s, const string& delimiters, empties_type empties/* = SplitType::empties_ok */)							    
{
	result.clear();
	size_t current;
	size_t next = -1;
	do
	{
		if (empties == no_empties)
		{
			next = s.find_first_not_of( delimiters, next + 1 );
			if (next == string::npos) break;
			next -= 1;
		}
		current = next + 1;
		next = s.find_first_of( delimiters, current );
		string res = s.substr( current, next - current );
		result.push_back(res);
	}
	while (next != string::npos);
	return result;
}

//parse vector string to CWordItem
CWordItem* CWordManager::ParseVectorString(vector<string>& data)
{
	int count = data.size();
	if(count < 0)
		return NULL;

	
	//rule: 
	//	Index	
	//	0(1st item)							term;
	//	1									pronunciation
	//  2 ~ (2+meansCount)th				means
	//	2+meansCount ~						sentences
	int meansCount = 5;
	string term = data[0];		
	long id = m_wordsMap.size();
	CWordItem* wordItem = new CWordItem(term, id);

	if(count > 1)
	{
		//add pronunciation;
		string pronunciation = data[1];	  
		wordItem->AddPronunciation(pronunciation);		
		
		//add means
		for(int i = 2; i < min(count, (2+meansCount)); i++)
		{
			string mean = data[i];
			wordItem->AddMean(mean);
		}
		
		//add sample sentences	
		for(int j = 2+meansCount; j < min(count, (2+meansCount)); j++)
		{
			string sentence = data[j];
			wordItem->AddSentence(sentence);
		}
	}
	
	return wordItem;
}