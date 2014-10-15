#include "cocos2d.h"

#include "cocos-ext.h"
#include "../DataStruct/WordItem.h"

using namespace cocos2d::extension;
using namespace cocos2d::ui;

USING_NS_CC;
using namespace std;

//This is a layer for Home view
class CHomeViewLayer : public CCLayerColor
{		
public:
	//create function;
	static CHomeViewLayer* create(const ccColor4B &color, const CCRect& rect);
	static CHomeViewLayer* create(const ccColor4B& layerColor, const CCRect& rect, 
		const char* termFontName, const char* otherFontName);

	//overload from CCLayer;
	virtual bool initWithColor(const ccColor4B& layerColor, const CCRect& rect, 
		const char* termFontName, const char* otherFontName);

	
protected:
	CHomeViewLayer();	
	virtual ~CHomeViewLayer();

	void SetupUI(const CCRect& rect,const char* termFontName, const char* otherFontName, int maxMeansLabel);
	 
	string m_termFontName;
	string m_otherFontName;

	CWordItem GetDailyWord();	//get daily word;

	CCLabelTTF*  AddDailyWordLabel(const string& str, const char *fontName, float fontSize, const ccColor3B& color, CCPoint curPos);	//add labels into vector
	void CreateDailyWordLabels(float& curY, int maxMeansLabel);		//create daily word labels;
public:
	std::vector<CCLabelTTF*> m_dailyWordLabels;

	//CCLayer* m_parentLayer;	//for cast touch msg from this layer to main layer;

	//Labels
	// 	vector<CCLabelTTF*> m_termLabels;
	// 	vector<CCLabelTTF*> m_pronunciationLabels;
	// 	vector<CCLabelTTF*> m_meansLabels;
	// 	vector<CCLabelTTF*> m_sampleSentencesLabels;
};