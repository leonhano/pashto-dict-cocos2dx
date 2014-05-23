#include "WordScrollViewLayer.h"
#include "UIManager.h"
									  
#define WORDSCROLLVIEW_MSG		"WordScrollView_MSG"

CWordScrolllViewLayer::CWordScrolllViewLayer()
{
	m_parentLayer = NULL;
}

CWordScrolllViewLayer::~CWordScrolllViewLayer()
{
}

CWordScrolllViewLayer * CWordScrolllViewLayer::create(const ccColor4B& layerColor, const CCRect& rect)
{
	CUIManager::UI_LAYOUT ui_layout = CUIManager::getInstance().ui_layout;
	return create(layerColor, rect, ui_layout.LABEL_DEFAULT_TERM_FONTNAME.c_str(), ui_layout.LABEL_DEFAULT_OTHER_FONTNAME.c_str());
}

CWordScrolllViewLayer * CWordScrolllViewLayer::create(const ccColor4B& layerColor, const CCRect& rect, 
													  const char* termFontName, const char* otherFontName)
{	
	CWordScrolllViewLayer * pLayer = new CWordScrolllViewLayer();
	if( pLayer && pLayer->initWithColor(layerColor, rect, termFontName, otherFontName))
	{
		pLayer->setPosition(ccp(rect.getMinX(), rect.getMinY()));
		pLayer->autorelease();
		return pLayer;
	}
	CC_SAFE_DELETE(pLayer);
	return NULL;
};
		  
//create ScrollView;
void CWordScrolllViewLayer::CreateScrollView(const CCSize& size)
{
	//create scrollview and container;
	m_scrollView = CCScrollView::create();
	m_scrollView->setViewSize(size);
	m_scrollView->setContentSize(size);
	this->addChild(m_scrollView);

	//setup container
	m_container = CCLayerColor::create(m_layerColor, size.width, size.height);
	m_container->setContentSize(size);
	m_scrollView->addChild(m_container);

	//init scrollview properties
	//m_scrollView->setPosition(ccp(rect.getMinX(), rect.getMinY()));	 
	m_scrollView->setDirection(kCCScrollViewDirectionVertical);	
	m_scrollView->setBounceable(true);
}

bool CWordScrolllViewLayer::initWithColor(const ccColor4B& layerColor, const CCRect& rect, 
										  const char* termFontName, const char* otherFontName)
{
	if (!CCLayer::init())
	{
		return false;
	}

	float width = rect.size.width;
	float height = rect.size.height;
	//base layer is invisiable, no color;
	if(!CCLayerColor::initWithColor(ccc4(0,0,0,0), width, height))
	{
		return false;
	}

	//init values;
	m_totalItemsHeight = 0;
	m_layerColor = layerColor;
	m_termFontName = termFontName;
	m_otherFontName = otherFontName;

	//enable touch event
	setTouchEnabled(true);

	//test: add msg notification;
	CCNotificationCenter::sharedNotificationCenter()->addObserver(m_scrollView, callfuncO_selector(CWordScrolllViewLayer::onMsgCenter), WORDSCROLLVIEW_MSG, NULL);

	CreateScrollView(rect.size);

	return true;
}

void CWordScrolllViewLayer::registerWithTouchDispatcher()
{ 
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);  
	CCLayer::registerWithTouchDispatcher();  
}

bool CWordScrolllViewLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	CCLog("touches begin:!!");

	CCNode* child = this;
	while((child != NULL) && (m_parentLayer == NULL))
	{
		CCNode* parent =  child->getParent();
		m_parentLayer = dynamic_cast<CCLayer*>(parent);

		if(m_parentLayer == NULL)
		{
			child =  parent;			
		}	
	}
	
	if(m_parentLayer)
		m_parentLayer->ccTouchBegan(pTouch, pEvent);
	return true;
}

void CWordScrolllViewLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	CCLog("touchesEnded:!!");	

	if(m_parentLayer)
		m_parentLayer->ccTouchEnded(pTouch, pEvent);
}

void CWordScrolllViewLayer::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{	
	CCLog("touches touchesCancelled:!!");	

	if(m_parentLayer)
		m_parentLayer->ccTouchCancelled(pTouch, pEvent);
}

void CWordScrolllViewLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{	
	CCLog("touches touchesMoved:!!");

	if(m_parentLayer)
		m_parentLayer->ccTouchMoved(pTouch, pEvent);
}

//set term font name;
// void CWordScrolllViewLayer::SetTermFont(string termFontName)
// {
// 	for(vector<CCLabelTTF*>::iterator it = m_termLabels.begin(); it != m_termLabels.end(); it++)
// 	{						   		
// 		CCLabelTTF* termLabel = &(*it);
// 		termLabel->setFontName(termFontName.c_str());
// 	}
// }

//clean all;
void CWordScrolllViewLayer::CleanAll()
{	  		  
	m_totalItemsHeight = 0;
// 	m_termLabels.clear();
// 	m_pronunciationLabels.clear();
// 	m_meansLabels.clear();
// 	m_sampleSentencesLabels.clear();

	m_scrollView = NULL;
	m_container = NULL;	   	

	this->removeAllChildrenWithCleanup(true);

	/*
	if(m_container)
	{
		m_container->removeAllComponents();
		m_container->removeAllChildrenWithCleanup(true);
	} 

	if(m_scrollView)
	{
		m_scrollView->removeAllComponents();			
		m_scrollView->removeAllChildrenWithCleanup(true);
	}  
	*/
	CCLog("CleanAll()");
}

void CWordScrolllViewLayer::RecreateAllItems()
{	
	CleanAll();	
	CCSize size = this->getContentSize();
	CreateScrollView(size);	
}

void CWordScrolllViewLayer::SetTextToDisplay(const char* str)
{
	RecreateAllItems();
	
	CUIManager::UI_LAYOUT ui_layout = CUIManager::getInstance().ui_layout;
	float labelHeight = max(ui_layout.LABEL_TERM_FONT_SIZE, ui_layout.LABEL_OTHER_FONT_SIZE) + ui_layout.LABEL_Y_MARGIN;
	float viewHeight = m_scrollView->getViewSize().height;

	//create term label
	CCLabelTTF* pTermLabel = CreateLabel(str, m_termFontName.c_str(), ui_layout.LABEL_TERM_FONT_SIZE, labelHeight, ccBLUE);		
	pTermLabel->setPosition(ccp(ui_layout.LABEL_X_MARGIN, viewHeight - (1.5 *ui_layout.LABEL_Y_MARGIN) ));	//top
	m_container->addChild(pTermLabel);

	m_scrollView->setTouchEnabled(false);
}

//set worditem to show
void CWordScrolllViewLayer::SetWordItemToDisplay(CWordItem* pWordItem, bool removeAllOldItems)
{	
	if(pWordItem == NULL)
		return;

	//if((removeAllOldItems) && (m_termLabels.size() > 0))
	if(removeAllOldItems)
	{
		RecreateAllItems();
	}

	CUIManager::UI_LAYOUT ui_layout = CUIManager::getInstance().ui_layout;
	float labelHeight = max(ui_layout.LABEL_TERM_FONT_SIZE, ui_layout.LABEL_OTHER_FONT_SIZE) + ui_layout.LABEL_Y_MARGIN;
	int labelCount = 0;

	//create term label
	CCLabelTTF* pTermLabel = CreateLabel(pWordItem->m_term, m_termFontName.c_str(), ui_layout.LABEL_TERM_FONT_SIZE, labelHeight, ccBLUE);
	labelCount++;	

	//create pronunciation label
	string pronunciation = 	pWordItem->m_pronunciation;
	CCLabelTTF* pPronunciationLabel = NULL;
	if(pronunciation.size() >0)
	{
		pPronunciationLabel = CreateLabel(pronunciation, m_otherFontName.c_str(), ui_layout.LABEL_OTHER_FONT_SIZE, labelHeight, ccBLACK);
		labelCount++;
	}
	
	//create means labels;
	vector<CCLabelTTF*> meansLabels;
	for(vector<string>::iterator meansIT = pWordItem->m_means.begin(); meansIT != pWordItem->m_means.end(); meansIT++)
	{
		string mean = *meansIT;
		if(mean.size() > 0)
		{
			CCLabelTTF * pLabel = CreateLabel(mean, m_otherFontName.c_str(), ui_layout.LABEL_OTHER_FONT_SIZE, labelHeight, ccBLACK);
			meansLabels.push_back(pLabel);
			labelCount++;
		}
	}
	
	//create sample sentences labels  
	vector<CCLabelTTF*> sampleSentencesLabels;
	for(vector<string>::iterator sampleIT =  pWordItem->m_sampleSentence.begin(); sampleIT != pWordItem->m_sampleSentence.end(); sampleIT++)
	{
		string sampleSentence = *sampleIT;
		if(sampleSentence.size() > 0)
		{
			CCLabelTTF * pLabel = CreateLabel(*sampleIT, m_otherFontName.c_str(), ui_layout.LABEL_OTHER_FONT_SIZE, labelHeight, ccBLACK);
			sampleSentencesLabels.push_back(pLabel);	
			labelCount++;
		}
	}

	//based on label to setup container size;     
	float deltaYPos(m_totalItemsHeight);

	float curTotalItemsHeight = labelCount * labelHeight + ui_layout.LABEL_Y_MARGIN;	//current total label height;
	m_totalItemsHeight += curTotalItemsHeight;								//total label height;
	float viewHeight = m_scrollView->getViewSize().height;

	//if labels can be contained in the view, do not scroll;
	if(m_totalItemsHeight <= viewHeight)
	{	  
		//m_scrollView->setBounceable(true);	  
		//m_container->setContentSize(CCSize(m_container->getContentSize().width, labelsHeight));
		m_scrollView->setTouchEnabled(false);
		deltaYPos = deltaYPos + viewHeight - curTotalItemsHeight - ui_layout.LABEL_Y_MARGIN;	
	}
	else
	{
		m_scrollView->setTouchEnabled(true);		
		m_scrollView->setContentSize(CCSize(m_scrollView->getViewSize().width, m_totalItemsHeight + ui_layout.LABEL_Y_MARGIN));
		m_container->setContentSize(CCSize(m_scrollView->getViewSize().width, m_totalItemsHeight + ui_layout.LABEL_Y_MARGIN));

		m_scrollView->setContentOffset(CCPoint(0.f, (viewHeight - 1.05f * m_totalItemsHeight)), false);
		//m_container->setPositionY(viewHeight - labelsHeight);
	}	

	//set labels position
	//set sample label position =  deltaYPos + height * index 
	int yPosIndex = 0;
	for(vector<CCLabelTTF*>::iterator sampleLabelIT = sampleSentencesLabels.begin(); sampleLabelIT != sampleSentencesLabels.end(); sampleLabelIT++)
	{
		CCLabelTTF * sampleLabel = *sampleLabelIT;
		sampleLabel->setPosition(ccp(ui_layout.LABEL_X_MARGIN, deltaYPos + (++yPosIndex) * labelHeight));
		m_container->addChild(sampleLabel);
	}

	//set means Label;
	for(vector<CCLabelTTF*>::iterator meansLabelIT = meansLabels.begin(); meansLabelIT != meansLabels.end(); meansLabelIT++)
	{
		CCLabelTTF *meansLabel = *meansLabelIT;
		meansLabel->setPosition(ccp(ui_layout.LABEL_X_MARGIN, deltaYPos + (++yPosIndex) * labelHeight));
		m_container->addChild(meansLabel);
	}

	//set term Label;
	if(pPronunciationLabel)
	{
		pPronunciationLabel->setPosition(ccp(ui_layout.LABEL_X_MARGIN, deltaYPos + (++yPosIndex) * labelHeight));
		m_container->addChild(pPronunciationLabel);
	}

	//set term Label;
	if(pTermLabel)
	{
		pTermLabel->setPosition(ccp(ui_layout.LABEL_X_MARGIN, deltaYPos + (++yPosIndex) * labelHeight));	//top
		m_container->addChild(pTermLabel);	 
	}

	CCLog("SetWordItemToDisplay()");

	//add all items into 
// 	m_termLabels.push_back(pTermLabel);
// 	m_pronunciationLabels.push_back(pPronunciationLabel);
// 	m_meansLabels.insert(m_meansLabels.end(), meansLabels.begin(), meansLabels.end());
// 	m_sampleSentencesLabels.insert(m_sampleSentencesLabels.end(), sampleSentencesLabels.begin(), sampleSentencesLabels.end());

}

void CWordScrolllViewLayer::SetWordItemVectorToDisplay(vector<CWordItem>* pWordItems, bool removeAllOldItems)
{							
	if(pWordItems->size() <0)
		return;

	//if((removeAllOldItems) && (m_termLabels.size() > 0))
	if(removeAllOldItems)
	{
		RecreateAllItems();
	}

	//wordItem1;
	for(vector<CWordItem>::iterator it = pWordItems->begin(); it != pWordItems->end(); it++)
	{
		CWordItem* pWordItem = &(*it);
		SetWordItemToDisplay(pWordItem, false);
	}	   	
}

//create label to add into this viewer;
CCLabelTTF* CWordScrolllViewLayer::CreateLabel (const string& str, const char *fontName, float fontSize, float height, const ccColor3B& color)
{
	if(str.size() <= 0)
		return NULL;

	CCLabelTTF* pLabel = CCLabelTTF::create(str.c_str(), fontName, fontSize);  
	pLabel->setAnchorPoint(ccp(0,0.5));

	CCSize size = m_container->getContentSize();  
	CCSize dimensions = CCSize(CCPoint(size.width, height))	;   
	
	CCLog("CreateLabel() !!!!! weird , in andorid, can't use  setDimensions");
	//!!!!! weird , in andorid, can't use  setDimensions"!!!!!!
	//pLabel->setDimensions(dimensions);  

	pLabel->setColor(color);
	pLabel->setHorizontalAlignment(kCCTextAlignmentLeft);  
	CCLog("CreateLabel()");
	return pLabel;
}

//Message center
void CWordScrolllViewLayer::onMsgCenter(CCObject* obj)
{
	  CCLayer * mainLayer = dynamic_cast<CCLayer*> (obj);

}