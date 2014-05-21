#include "WordItem.h"
#include "cocos2d.h" 

USING_NS_CC;

#define STRING_SEPERATOR "|$|"
#define STRING_TERM_TAG "$TERM$"
#define STRING_ID_TAG "$ID$"
#define STRING_PRONUNCIATION_TAG "$PRON$"
#define STRING_MEANS_TAG "$MEANS$"
#define STRING_SAMPLE_TAG "$SAMPLE$"

CWordItem::CWordItem(const string &term, long id)
	: m_term(term), m_id(id)
{
}

CWordItem::CWordItem(const string &term, long id, const string &pronunciation)
	: m_term(term), m_id(id), m_pronunciation(pronunciation)
{
}

CWordItem::CWordItem(const string &term, long id, const vector<string> &means)
	: m_term(term), m_id(id), m_means(means)
{
}

CWordItem::CWordItem(const string &term, long id, const vector<string> &means, const vector<string> &sampleSentence)
	: m_term(term), m_id(id), m_means(means), m_sampleSentence(sampleSentence)
{
}

CWordItem::CWordItem(const string &term, long id, const string &pronunciation, const vector<string> &means, const vector<string> &sampleSentence)
	: m_term(term), m_id(id), m_pronunciation(pronunciation), m_means(means), m_sampleSentence(sampleSentence)
{
}

CWordItem::~CWordItem(void)
{
}

void CWordItem::AddPronunciation(const string &pronunciation)
{
	if(pronunciation.size() > 0)
		m_pronunciation = pronunciation;
	else
	{
		CCLog("Error! Failed to add pronunciation!  term = %s, id = %d", m_term.c_str(), (int)m_id);
	}
}

void CWordItem::AddMean(const string &mean)
{		  
	if(mean.size() > 0)
		m_means.push_back(mean);
	else
	{
		CCLog("Error! Failed to add mean!  term = %s, id = %d",  m_term.c_str(), (int)m_id);
	}
}

void CWordItem::AddSentence(const string &sentence)
{
	if(sentence.size() > 0)
		m_sampleSentence.push_back(sentence);
	else
	{
		CCLog("Error! Failed to add sentence!  term = %s, id = %d",  m_term.c_str(), (int)m_id);
	}
}

string CWordItem::TAGString()
{
	string temp = TermTAGString();
	temp = temp +IdTAGString();
	temp = temp + PronunciationTAGString();
	temp = temp + MeansTAGString();
	temp = temp + SentencesTAGString();
	return temp;
}

string CWordItem::IdTAGString()
{ 
	string temp =  STRING_ID_TAG + IntToString(m_id);

	//string temp = STRING_ID_TAG + std::to_string(long double(m_id));
	return temp;
}

string CWordItem::TermTAGString()
{
	string temp = STRING_TERM_TAG + m_term;
	return temp;
}
string CWordItem::PronunciationTAGString()
{
	string temp = STRING_PRONUNCIATION_TAG + m_pronunciation;
	return temp;
}

string CWordItem::MeansTAGString()
{
	string temp;
	for(vector<string>::iterator it = m_means.begin(); it!= m_means.end(); ++it)
	{
		temp = temp + STRING_MEANS_TAG;
		temp = temp + *it;		
	}
	return temp;
}

string CWordItem::SentencesTAGString()
{
	string temp;
	for(vector<string>::iterator it = m_sampleSentence.begin(); it!= m_sampleSentence.end(); ++it)
	{
		temp = temp + STRING_SAMPLE_TAG;
		temp = temp + *it;		
	}
	return temp;
}

vector<string> CWordItem::ToString()
{
	vector<string> output;
	output.push_back(TermToString());
	output.push_back(PronunciationToString());

	vector<string> means = MeansToString();
	output.insert(output.end(), means.begin(), means.end());

	vector<string> sampleSeneteces = SentencesToString();
	output.insert(output.end(), sampleSeneteces.begin(), sampleSeneteces.end());
	return output;
}

string CWordItem::IdToString()
{
	return IntToString(m_id);
}

string CWordItem::TermToString()
{
	return m_term;
}

string CWordItem::PronunciationToString()
{
	return m_pronunciation;
}

vector<string> CWordItem::MeansToString()
{
	vector<string> output;
	int index = 1;
	string temp;
	for(vector<string>::iterator it = m_means.begin(); it!= m_means.end(); ++it)
	{
		temp = IntToString(index++) + ". ";
		temp = temp + *it;
		output.push_back(temp);
	}
	return output;
}

vector<string> CWordItem::SentencesToString()
{
	vector<string> output;
	int index = 1;
	string temp;
	for(vector<string>::iterator it = m_sampleSentence.begin(); it!= m_sampleSentence.end(); ++it)
	{
		temp = IntToString(index++) + ". ";
		temp = temp + *it;
		output.push_back(temp);
	}
	return output;
}
