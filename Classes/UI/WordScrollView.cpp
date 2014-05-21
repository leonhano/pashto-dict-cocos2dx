#include "WordScrollView.h"
#include "UIManager.h"
									  
#define WORDSCROLLVIEW_MSG		"WordScrollView_MSG"

/*
CWordScrolllView::CWordScrolllView()
{
	m_scrollView = NULL;
	m_container = NULL;	//container

	//Labels
	m_termLabel = NULL;
	m_pronunciationLabel = NULL;

	m_container = NULL;
	m_scrollView = NULL;	
}
*/

CWordScrolllView::~CWordScrolllView()
{

	m_termLabel = NULL;
	m_pronunciationLabel = NULL;
	m_meansLabels.clear();
	m_sampleSentencesLabels.clear();

	if(m_container!= NULL)
	{
		m_container->removeAllComponents();
		m_container->removeAllChildrenWithCleanup(true);
	} 

	if(m_scrollView != NULL)
	{					   		
		m_scrollView->setTouchEnabled(false);
		m_scrollView->removeAllComponents();			
		m_scrollView->removeAllChildrenWithCleanup(true);
		m_container = NULL;
		m_scrollView = NULL;
	}
}

CWordScrolllView::CWordScrolllView(CCRect rect, CCNode *container, CWordItem* pWordItem )
{												
	CCLog("CWordScrolllView()");
	m_bIsTouchEnabled = true;	//touch enabled;

	m_scrollView = CCScrollView::create();
	m_scrollView->setViewSize(rect.size);
	m_scrollView->setContentSize(rect.size);
	//setup container
	m_container = CCLayerColor::create(ccc4(10, 10, 10, 120), rect.size.width, rect.size.height);
	m_container->setContentSize(rect.size);
	m_scrollView->addChild(m_container);

	//init scrollview properties
	m_scrollView->setPosition(ccp(rect.getMinX(), rect.getMinY()));	 
	m_scrollView->setDirection(kCCScrollViewDirectionVertical);	
	m_scrollView->setBounceable(true);

	if(container != NULL)
		container->addChild(m_scrollView);

	//test: add msg notification;
	CCNotificationCenter::sharedNotificationCenter()->addObserver(m_scrollView, callfuncO_selector(CWordScrolllView::onMsgCenter), WORDSCROLLVIEW_MSG, NULL);

	SetWordItemToDisplay(pWordItem);
}
  
bool CWordScrolllView::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	if(m_bIsTouchEnabled)
	{
	   CCLog("touches begin:!!");
	   return true;
	}
	else
		return false;
}

void CWordScrolllView::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	if(!m_bIsTouchEnabled)
		return;

	CCLog("touchesEnded:!!");
}

void CWordScrolllView::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{	  
	if(!m_bIsTouchEnabled)
		return;

	CCLog("touches touchesCancelled:!!");
}

void CWordScrolllView::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{	  	  
	if(!m_bIsTouchEnabled)
		return;

	CCLog("touches touchesMoved:!!");
}

//set term font name;
void CWordScrolllView::SetTermFont(string termFontName)
{
	if(m_termLabel)
		m_termLabel->setFontName(termFontName.c_str());
}
	 
//set worditem to show
void CWordScrolllView::SetWordItemToDisplay(CWordItem* pWordItem)
{	
	if(pWordItem == NULL)
		return;

	CUIManager::UI_LAYOUT ui_layout = CUIManager::getInstance().ui_layout;
	float labelHeight = max(ui_layout.LABEL_TERM_FONT_SIZE, ui_layout.LABEL_OTHER_FONT_SIZE) + ui_layout.LABEL_Y_MARGIN;

	//create term label
	string term = pWordItem->m_term;
	m_termLabel = CreateLabel(term, ui_layout.LABEL_DEFAULT_TERM_FONTNAME.c_str(), ui_layout.LABEL_TERM_FONT_SIZE, labelHeight, ccBLUE);

	//create pronunciation label
	m_pronunciationLabel = CreateLabel(pWordItem->m_pronunciation, ui_layout.LABEL_DEFAULT_OTHER_FONTNAME.c_str(), ui_layout.LABEL_OTHER_FONT_SIZE, labelHeight, ccBLACK);

	//create means labels;
	for(vector<string>::iterator meansIT = pWordItem->m_means.begin(); meansIT != pWordItem->m_means.end(); meansIT++)
	{
		CCLabelTTF * pLabel = CreateLabel(*meansIT, ui_layout.LABEL_DEFAULT_OTHER_FONTNAME.c_str(), ui_layout.LABEL_OTHER_FONT_SIZE, labelHeight, ccBLACK);
		m_meansLabels.push_back(pLabel);
	}

	//create sample sentences labels
	for(vector<string>::iterator sampleIT =  pWordItem->m_sampleSentence.begin(); sampleIT != pWordItem->m_sampleSentence.end(); sampleIT++)
	{
		CCLabelTTF * pLabel = CreateLabel(*sampleIT, ui_layout.LABEL_DEFAULT_OTHER_FONTNAME.c_str(), ui_layout.LABEL_OTHER_FONT_SIZE, labelHeight, ccBLACK);
		m_sampleSentencesLabels.push_back(pLabel);
	}

	//based on label to setup container size;
	int labelCount = 2 + m_meansLabels.size() + m_sampleSentencesLabels.size();
	float totalHeight = labelCount * labelHeight + ui_layout.LABEL_Y_MARGIN;	//total label height;
	float viewHeight = m_scrollView->getViewSize().height;

	float deltaYPos(0);

	//if labels can be contained in the view, do not scroll;
	if(totalHeight <= viewHeight)
	{	  
		//m_scrollView->setBounceable(true);	  
		//m_container->setContentSize(CCSize(m_container->getContentSize().width, labelsHeight));
		m_scrollView->setTouchEnabled(false);
		deltaYPos = viewHeight - totalHeight - ui_layout.LABEL_Y_MARGIN;	
	}
	else
	{
		m_scrollView->setTouchEnabled(true);		
		m_scrollView->setContentSize(CCSize(m_scrollView->getViewSize().width, totalHeight + ui_layout.LABEL_Y_MARGIN));
		m_container->setContentSize(CCSize(m_scrollView->getViewSize().width, totalHeight + ui_layout.LABEL_Y_MARGIN));

		m_scrollView->setContentOffset(CCPoint(0.f, (viewHeight - 1.05f * totalHeight)), false);
		//m_container->setPositionY(viewHeight - labelsHeight);
	}	

	//set labels position
	//set sample label position =  deltaYPos + height * index 
	int yPosIndex = 0;
	for(vector<CCLabelTTF*>::iterator sampleLabelIT = m_sampleSentencesLabels.begin(); sampleLabelIT != m_sampleSentencesLabels.end(); sampleLabelIT++)
	{
		CCLabelTTF * sampleLabel = *sampleLabelIT;
		sampleLabel->setPosition(ccp(ui_layout.LABEL_X_MARGIN, deltaYPos + (++yPosIndex) * labelHeight));
		m_container->addChild(sampleLabel);
	}

	//set means Label;
	for(vector<CCLabelTTF*>::iterator meansLabelIT = m_meansLabels.begin(); meansLabelIT != m_meansLabels.end(); meansLabelIT++)
	{
		CCLabelTTF *meansLabel = *meansLabelIT;
		meansLabel->setPosition(ccp(ui_layout.LABEL_X_MARGIN, deltaYPos + (++yPosIndex) * labelHeight));
		m_container->addChild(meansLabel);
	}
	 
	//set term Label;
	m_pronunciationLabel->setPosition(ccp(ui_layout.LABEL_X_MARGIN, deltaYPos + (++yPosIndex) * labelHeight));
	m_container->addChild(m_pronunciationLabel);

	//set term Label;
	m_termLabel->setPosition(ccp(ui_layout.LABEL_X_MARGIN, deltaYPos + (++yPosIndex) * labelHeight));	//top
	m_container->addChild(m_termLabel);	 

	CCLog("SetWordItemToDisplay()");
}

//create label to add into this viewer;
CCLabelTTF* CWordScrolllView::CreateLabel (const string& str, const char *fontName, float fontSize, float height, const ccColor3B& color)
{
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
void CWordScrolllView::onMsgCenter(CCObject* obj)
{
	  CCLayer * mainLayer = dynamic_cast<CCLayer*> (obj);

}