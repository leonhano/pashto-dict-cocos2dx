
#include "HomeViewLayer.h" 
#include "UIManager.h"
#include "UITools.h"
#include "DataStruct/WordManager.h"

CHomeViewLayer::CHomeViewLayer()
{
	//m_parentLayer = NULL;


}

CHomeViewLayer::~CHomeViewLayer()
{
}

CHomeViewLayer * CHomeViewLayer::create(const ccColor4B& layerColor, const CCRect& rect)
{
	CUIManager::UI_LAYOUT ui_layout = CUIManager::getInstance().ui_layout;
	return create(layerColor, rect, ui_layout.LABEL_DEFAULT_TERM_FONTNAME.c_str(), ui_layout.LABEL_DEFAULT_OTHER_FONTNAME.c_str());
}

CHomeViewLayer * CHomeViewLayer::create(const ccColor4B& layerColor, const CCRect& rect, 
													  const char* termFontName, const char* otherFontName)
{	
	CHomeViewLayer * pLayer = new CHomeViewLayer();
	if( pLayer && pLayer->initWithColor(layerColor, rect, termFontName, otherFontName))
	{
		pLayer->setPosition(ccp(rect.getMinX(), rect.getMinY()));
		pLayer->autorelease();
		return pLayer;
	}
	CC_SAFE_DELETE(pLayer);
	return NULL;
}; 

bool CHomeViewLayer::initWithColor(const ccColor4B& layerColor, const CCRect& rect, 
									const char* termFontName, const char* otherFontName)
{
	if (!CCLayer::init())
	{
		return false;
	}

	float width = rect.size.width;
	float height = rect.size.height;
	//base layer is invisiable, no color;
	if(!CCLayerColor::initWithColor(layerColor, width, height))
	{
		return false;
	}
	this->setAnchorPoint(ccp(1,0));

	//enable touch event
	setTouchEnabled(true);
	 
	//init values;
	m_termFontName = termFontName;
	m_otherFontName = otherFontName;

	///set up UI;
	int maxMeansLabel = 2;
	SetupUI(rect,termFontName, otherFontName, maxMeansLabel);
	return true;
}

//************************************
// Method:    SetupUI
// FullName:  CHomeViewLayer::SetupUI
// Access:    protected 
// Returns:   void
// Qualifier: setup UI
// Parameter: const CCRect & rect   : whole 
// Parameter: const char * termFontName   :
// Parameter: const char * otherFontName   :
// Parameter: int maxMeansLabel   :
//************************************
void CHomeViewLayer::SetupUI(const CCRect& rect, const char* termFontName, const char* otherFontName, int maxMeansLabel)
{
	CUIManager::UI_LAYOUT ui_layout = CUIManager::getInstance().ui_layout;	

	float curY = rect.size.height - (1.5 *ui_layout.LABEL_Y_MARGIN);
	//static label
	CCLabelTTF* pStatementLabel = AddDailyWordLabel("Daily Word View", m_termFontName.c_str(), ui_layout.LABEL_NORMAL_FONT_SIZE, ccBLUE, ccp(ui_layout.LABEL_X_MARGIN, curY));		
	
	//----------create all daily word labels;-----------//
	curY = curY - pStatementLabel->getContentSize().height - ui_layout.LABEL_Y_MARGIN;
	CreateDailyWordLabels(curY, maxMeansLabel);
}

///
//************************************
// Method:    CreateDailyWordLabels
// FullName:  CHomeViewLayer::CreateDailyWordLabels
// Access:    protected 
// Returns:   void
// Qualifier: create daily word labels
// Parameter: float & curY   :  current y position (return it)
// Parameter: int maxMeansLabel   : max means label
//************************************
void CHomeViewLayer::CreateDailyWordLabels(float& curY, int maxMeansLabel)
{
	CUIManager::UI_LAYOUT ui_layout = CUIManager::getInstance().ui_layout;	

	CWordItem dailyWord = GetDailyWord();	//get daily word;
	//daily word term label
	CCLabelTTF* pDailyWordTermLabel = AddDailyWordLabel(dailyWord.m_term, m_termFontName.c_str(), ui_layout.LABEL_TERM_FONT_SIZE, ccBLUE, ccp(ui_layout.LABEL_X_MARGIN, curY));			 

	//means label;	
	int meansCount = 0;
	curY = curY - pDailyWordTermLabel->getContentSize().height - ui_layout.LABEL_Y_MARGIN;
	for(vector<string>::iterator meansIT = dailyWord.m_means.begin(); meansIT != dailyWord.m_means.end(); meansIT++)
	{
		if(meansCount > maxMeansLabel)
			break;

		string mean = *meansIT;
		if(mean.size() > 0)
		{			
			CCLabelTTF * pMeanLabel = AddDailyWordLabel(mean, m_otherFontName.c_str(), ui_layout.LABEL_OTHER_FONT_SIZE, ccBLACK, ccp(ui_layout.LABEL_X_MARGIN, curY));			
			curY = curY - pMeanLabel->getContentSize().height - ui_layout.LABEL_Y_MARGIN;

			meansCount++;
		}
	}

	//just show first sample 
	for(vector<string>::iterator sampleIT =  dailyWord.m_sampleSentence.begin(); sampleIT != dailyWord.m_sampleSentence.end(); sampleIT++)
	{
		string sampleSentence = *sampleIT;
		if(sampleSentence.size() > 0)
		{
			CCLabelTTF * pSampleSentenceLabel = AddDailyWordLabel(*sampleIT, m_otherFontName.c_str(), ui_layout.LABEL_OTHER_FONT_SIZE, ccBLACK, ccp(ui_layout.LABEL_X_MARGIN, curY));			
			curY = curY - pSampleSentenceLabel->getContentSize().height - ui_layout.LABEL_Y_MARGIN;
			break;
		}
	}
}

//************************************
// Method:    GetDailyWord
// FullName:  CHomeViewLayer::GetDailyWord
// Access:    protected 
// Returns:   CWordItem
// Qualifier: Get Daily word;
//************************************
CWordItem CHomeViewLayer::GetDailyWord()
{
	map<string, vector<CWordItem> >* pWordMap = &(CWordManager::getInstance().m_wordsMap);
	int id = (int)rand()%(pWordMap->size()); 


	map<string, vector<CWordItem> >::iterator it = pWordMap->begin();
	std::advance(it, id);
	string thisKey = it->first;
	vector<CWordItem> wordItems = it->second;
	//CCLog("Daily word: id = %d  ||  term = %s", id, wordItems.begin()->m_term);
	return wordItems.front();
}

CCLabelTTF* CHomeViewLayer::AddDailyWordLabel(const string& str, const char *fontName, float fontSize, const ccColor3B& color, CCPoint curPos)
{
	CUIManager::UI_LAYOUT ui_layout = CUIManager::getInstance().ui_layout;
	float labelWidth = this->getContentSize().width - 2 * ui_layout.LABEL_X_MARGIN;
	CCLabelTTF* pLabel = UITools::CreateLabel(str, fontName, fontSize, color, labelWidth);	
	pLabel->setPosition(curPos);		
	this->addChild(pLabel);
	m_dailyWordLabels.push_back(pLabel);
	return pLabel;
}