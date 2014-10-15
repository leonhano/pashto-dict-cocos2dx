#include "MainPageView.h"
#include "datastruct\WordItem.h"
#include "DataStruct\WordManager.h"
#include "WordScrollViewLayer.h"
#include "UIManager.h"

using namespace std;

CMainPageView * CMainPageView::create(CCRect pageviewRect)
{	  
	CMainPageView* widget = new CMainPageView();
	if (widget && widget->init(pageviewRect))
	{
		widget->autorelease();
		return widget;
	}
	CC_SAFE_DELETE(widget);
	return NULL;
}


void CMainPageView::onEnter()
{
	Layout::onEnter();
	scheduleUpdate();
}

bool CMainPageView::init(CCRect pageviewRect)
{							  	
	//code u initialization
	this->setTouchEnabled(true);
	this->setSize(pageviewRect.size);
	this->setPosition(pageviewRect.origin);
	
	CUIManager::UI_LAYOUT ui_layout = CUIManager::getInstance().ui_layout;

	//test for scrollview;
	vector<CWordItem>* wordItems = CWordManager::getInstance().GetWords("ابابیله");	
	if(wordItems)
	{	
		CWordScrolllViewLayer* m_pWordScrollViewLayer = CWordScrolllViewLayer::create(ccc4(173,207,255,180), ui_layout.Word_Show_Layer_Rect);
		m_pWordScrollViewLayer->SetWordItemVectorToDisplay(wordItems, true);
		this->addWidgetToPage(m_pWordScrollViewLayer, 0, false);
	}

	return UIPageView::init();
}