#include "WordScrollViewLayer.h"
#include "UIManager.h"
#include "UITools.h"
									  
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
	m_totalItemsHeight = 0;

	//create scrollview and container;
	m_scrollView = CCScrollView::create();
	m_scrollView->setViewSize(size);
	m_scrollView->setContentSize(size);
	this->addChild(m_scrollView);

	//setup container
	m_container = CCLayerColor::create(m_layerColor, size.width, size.height);
	m_container->setContentSize(size);
	m_container->setTouchEnabled(true);
	m_scrollView->addChild(m_container);

	//init scrollview properties
	//m_scrollView->setPosition(ccp(rect.getMinX(), rect.getMinY()));	 
	m_scrollView->setDirection(kCCScrollViewDirectionVertical);	
	m_scrollView->setBounceable(true);
	m_scrollView->setTouchEnabled(false);
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
	setTouchEnabled(true);  //very important, true: open horizon touch for parent, false: just local touch;

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
	CCPoint delta = pTouch->getDelta();
	//CCLog("touches touchesMoved:!!  delta = %f, %f", delta.x, delta.y);
	if(m_totalItemsHeight>m_scrollView->getContentSize().height)
		m_scrollView->setTouchEnabled(true);

	//m_scrollView->setContentOffset(CCPoint(0,delta.y), true);

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
	float viewHeight = m_scrollView->getViewSize().height;

	//create term label
	float labelWidth = m_scrollView->getViewSize().width - 2 * ui_layout.LABEL_X_MARGIN;
	CCLabelTTF* pTermLabel = UITools::CreateLabel(str, m_termFontName.c_str(), ui_layout.LABEL_TERM_FONT_SIZE, ccBLUE, labelWidth);
	
	pTermLabel->setPosition(ccp(ui_layout.LABEL_X_MARGIN, viewHeight - pTermLabel->getContentSize().height));	//top
	m_container->addChild(pTermLabel);

	m_totalItemsHeight += pTermLabel->getContentSize().height;

	if(m_totalItemsHeight>m_scrollView->getContentSize().height)
		m_scrollView->setTouchEnabled(true);
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
	m_totalItemsHeight += ui_layout.LABEL_Y_MARGIN;
	int labelCount = 0;

	//create term label
	float labelWidth = m_scrollView->getViewSize().width - 2 * ui_layout.LABEL_X_MARGIN;
	CCLabelTTF* pTermLabel = UITools::CreateLabel(pWordItem->m_term, m_termFontName.c_str(), ui_layout.LABEL_TERM_FONT_SIZE, ccBLUE, labelWidth);
	labelCount++;	
	m_totalItemsHeight += pTermLabel->getContentSize().height;

	//create pronunciation label
	string pronunciation = 	pWordItem->m_pronunciation;
	CCLabelTTF* pPronunciationLabel = NULL;
	if(pronunciation.size() >0)
	{
		pPronunciationLabel = UITools::CreateLabel(pronunciation, m_otherFontName.c_str(), ui_layout.LABEL_OTHER_FONT_SIZE, ccBLACK, labelWidth);
		labelCount++;
		m_totalItemsHeight += pPronunciationLabel->getContentSize().height;
	}
	
	//create means labels;
	vector<CCLabelTTF*> meansLabels;
	for(vector<string>::iterator meansIT = pWordItem->m_means.begin(); meansIT != pWordItem->m_means.end(); meansIT++)
	{
		string mean = *meansIT;
		if(mean.size() > 0)
		{
			CCLabelTTF * pLabel = UITools::CreateLabel(mean, m_otherFontName.c_str(), ui_layout.LABEL_OTHER_FONT_SIZE, ccBLACK, labelWidth);
			meansLabels.push_back(pLabel);
			labelCount++;
			m_totalItemsHeight += pLabel->getContentSize().height;
		}
	}
	
	//create sample sentences labels  
	vector<CCLabelTTF*> sampleSentencesLabels;
	for(vector<string>::iterator sampleIT =  pWordItem->m_sampleSentence.begin(); sampleIT != pWordItem->m_sampleSentence.end(); sampleIT++)
	{
		string sampleSentence = *sampleIT;
		if(sampleSentence.size() > 0)
		{
			CCLabelTTF * pLabel = UITools::CreateLabel(*sampleIT, m_otherFontName.c_str(), ui_layout.LABEL_OTHER_FONT_SIZE, ccBLACK, labelWidth);
			sampleSentencesLabels.push_back(pLabel);	
			labelCount++;
			m_totalItemsHeight += pLabel->getContentSize().height;
		}
	}

	//based on label to setup container size;     	;
	float viewHeight = m_scrollView->getViewSize().height;

	//if labels can be contained in the view, do not scroll;
	if(m_totalItemsHeight <= viewHeight)
	{	  
		//m_scrollView->setBounceable(true);	  
		//m_container->setContentSize(CCSize(m_container->getContentSize().width, labelsHeight));
		m_scrollView->setTouchEnabled(false);
	}
	else
	{
		m_scrollView->setTouchEnabled(true);		
		m_scrollView->setContentSize(CCSize(m_scrollView->getViewSize().width, m_totalItemsHeight));
		m_container->setContentSize(CCSize(m_scrollView->getViewSize().width, m_totalItemsHeight));

		//m_scrollView->setContentOffset(CCPoint(0.f, (viewHeight - 1.05f * m_totalItemsHeight)), false);
		//m_container->setPositionY(viewHeight - labelsHeight);
	}	

	//set labels position
	//set sample label position =  deltaYPos + height * index 
	int yPosIndex = -1;
	float labelHeight = max((float)(0), m_scrollView->getViewSize().height-m_totalItemsHeight);
	for(vector<CCLabelTTF*>::iterator sampleLabelIT = sampleSentencesLabels.begin(); sampleLabelIT != sampleSentencesLabels.end(); sampleLabelIT++)
	{
		CCLabelTTF * sampleLabel = *sampleLabelIT;
		sampleLabel->setPosition(ccp(ui_layout.LABEL_X_MARGIN, labelHeight));
		m_scrollView->addChild(sampleLabel);
		labelHeight += sampleLabel->getContentSize().height;
	}

	//set means Label;
	for(vector<CCLabelTTF*>::iterator meansLabelIT = meansLabels.begin(); meansLabelIT != meansLabels.end(); meansLabelIT++)
	{
		CCLabelTTF *meansLabel = *meansLabelIT;
		meansLabel->setPosition(ccp(ui_layout.LABEL_X_MARGIN, labelHeight));
		m_scrollView->addChild(meansLabel);
		labelHeight += meansLabel->getContentSize().height;
	}

	//set term Label;
	if(pPronunciationLabel)
	{
		pPronunciationLabel->setPosition(ccp(ui_layout.LABEL_X_MARGIN, labelHeight));
		m_scrollView->addChild(pPronunciationLabel);
		labelHeight += pPronunciationLabel->getContentSize().height;
	}

	//set term Label;
	if(pTermLabel)
	{
		pTermLabel->setPosition(ccp(ui_layout.LABEL_X_MARGIN, labelHeight));	//top
		m_scrollView->addChild(pTermLabel);	 
		labelHeight += pTermLabel->getContentSize().height;
	}

	float finalPos = pTermLabel->getPositionY();

	CCLog("SetWordItemToDisplay()");

	//add all items into 
// 	m_termLabels.push_back(pTermLabel);
// 	m_pronunciationLabels.push_back(pPronunciationLabel);
// 	m_meansLabels.insert(m_meansLabels.end(), meansLabels.begin(), meansLabels.end());
// 	m_sampleSentencesLabels.insert(m_sampleSentencesLabels.end(), sampleSentencesLabels.begin(), sampleSentencesLabels.end());

	//show top of this viewer(in scroll view)
	if(viewHeight < m_totalItemsHeight)
		m_scrollView->setContentOffset(CCPoint(0, viewHeight - m_totalItemsHeight), false);
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

//Message center
void CWordScrolllViewLayer::onMsgCenter(CCObject* obj)
{
	  CCLayer * mainLayer = dynamic_cast<CCLayer*> (obj);

}