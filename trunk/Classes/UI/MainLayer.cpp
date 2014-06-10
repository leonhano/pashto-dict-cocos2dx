#include "MainLayer.h"
#include "CocoStudio\GUI\UIWidgets\UITextField.h"
#include "UIManager.h"
#include "GUI\CCScrollView\CCScrollView.h"
#include "ccTypes.h"
#include "CocoStudio\GUI\BaseClasses\UIWidget.h"
#include "DataStruct\WordManager.h"


CCScene* CMainLayer::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    CMainLayer* layer = CMainLayer::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

void CMainLayer::OnEnter()
{

}

void CMainLayer::OnExit()
{
// 	if(m_pWordScrollViewLayer != NULL)
// 		delete m_pWordScrollViewLayer;
}

// on "init" you need to initialize your instance
bool CMainLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(CMainLayer::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

    /////////////////////////////
	// 3. add your codes below...
	
	CUIManager::UI_LAYOUT ui_layout = CUIManager::getInstance().ui_layout;
	
	//------------whole layer---------------//
	//CCLayerColor* whole_layer = CCLayerColor::create(ccc4(100,100,10,255), ui_layout.Whole_Layer_Size.width, ui_layout.Whole_Layer_Size.height);
	CCSprite* whole_layer = CCSprite::create("background1.png");
	whole_layer->setTag(ui_layout.TAG_whole_layer);
	whole_layer->setAnchorPoint(CCPointZero);
	whole_layer->setPosition(CCPointZero);
	this->addChild(whole_layer, 0);	 

	//background image;
	CCSprite* bk_Img = CCSprite::create("Key_TextField.png");
	bk_Img->setTag(ui_layout.TAG_bk_Img);
	bk_Img->setAnchorPoint(CCPointZero);
	bk_Img->setPosition(ui_layout.IMG_TextField_Rect.origin);
	whole_layer->addChild(bk_Img, 1);
	
	//------------- UI layer ------------//
	m_pUILayer = UILayer::create();
	m_pUILayer->setTag(ui_layout.TAG_m_pUILayer);
	m_pUILayer->scheduleUpdate();
	addChild(m_pUILayer);

	//-------- Create the textfield --------
	UITextField* keyTextField = UITextField::create(); 
	keyTextField->setTag(ui_layout.TAG_keyTextField);
	keyTextField->setMaxLengthEnabled(true); 
	keyTextField->setMaxLength(20);
	keyTextField->setTouchEnabled(true);
	keyTextField->setFontName("Arial");
	keyTextField->setFontSize(ui_layout.FONTSIZE_KEY_TEXTFIELD);
	keyTextField->setPlaceHolder("input words here");
	keyTextField->setAnchorPoint(CCPointZero);
	keyTextField->setPosition(ui_layout.Input_TextField_Rect.origin);
	keyTextField->setTextHorizontalAlignment(kCCTextAlignmentRight);
	keyTextField->addEventListenerTextField(this, textfieldeventselector(CMainLayer::textFieldEvent));
	m_pUILayer->addWidget(keyTextField);
			
	//--------create section buttons--------//
	
	//word btn
	m_sectionWordbtn = UIButton::create();
	m_sectionWordbtn->setTag(ui_layout.TAG_sectionWordbtn);
	m_sectionWordbtn->loadTextures(ui_layout.Section_Button_Texture_Normal, ui_layout.Section_Button_Texture_Selected, ui_layout.Section_Button_Texture_Disabled);
	m_sectionWordbtn->setColor(ui_layout.Section_Area_Bkg_Color);
	m_sectionWordbtn->setTitleFontName(ui_layout.Section_Button_FontName);
	m_sectionWordbtn->setTitleFontSize(ui_layout.Section_Button_FontSize);
	m_sectionWordbtn->setTitleColor(ui_layout.Section_Button_TextColor);
	m_sectionWordbtn->setTitleText(ui_layout.Section_Word_Button_Text);
	m_sectionWordbtn->setPosition(ui_layout.Section_Word_Button_Rect.origin);
	m_sectionWordbtn->setSize(ui_layout.Section_Word_Button_Rect.size);
	m_sectionWordbtn->setVisible(true);
	m_sectionWordbtn->setTouchEnabled(true);
	m_sectionWordbtn->setFocused(true);
	m_sectionWordbtn->addTouchEventListener(this, toucheventselector(CMainLayer::sectionButtonsCallback));
	m_pUILayer->addWidget(m_sectionWordbtn);

	//donation btn
	m_sectionDonationbtn = UIButton::create();
	m_sectionDonationbtn->setTag(ui_layout.TAG_sectionDonationbtn);
	m_sectionDonationbtn->loadTextures(ui_layout.Section_Button_Texture_Normal, ui_layout.Section_Button_Texture_Selected, ui_layout.Section_Button_Texture_Disabled);
	m_sectionDonationbtn->setColor(ui_layout.Section_Area_Bkg_Color);
	m_sectionDonationbtn->setTitleFontName(ui_layout.Section_Button_FontName);
	m_sectionDonationbtn->setTitleFontSize(ui_layout.Section_Button_FontSize);
	m_sectionDonationbtn->setTitleColor(ui_layout.Section_Button_TextColor);
	m_sectionDonationbtn->setTitleText(ui_layout.Section_Donation_Button_Text);
	m_sectionDonationbtn->setPosition(ui_layout.Section_Donation_Button_Rect.origin);
	m_sectionDonationbtn->setSize(ui_layout.Section_Donation_Button_Rect.size);
	m_sectionDonationbtn->setVisible(true);
	m_sectionDonationbtn->setTouchEnabled(true);
	m_sectionDonationbtn->setFocused(false);
	m_sectionDonationbtn->addTouchEventListener(this, toucheventselector(CMainLayer::sectionButtonsCallback));
	m_pUILayer->addWidget(m_sectionDonationbtn);

	/* 
	//load main layer from json file;
	m_pLayout = dynamic_cast<Layout*> (GUIReader::shareReader()->widgetFromJsonFile("MainLayer_1/MainLayer_1.json"));
	if(m_pLayout)
	{
		//this->addChild(m_pLayout);
		m_pUILayer->addWidget(m_pLayout);
	}	

	//Term label		
	ShowTerm("Hello word");
	//register text field event
	UITextField *keyTextField = dynamic_cast<UITextField*> (m_pUILayer->getWidgetByName(UI_KEY_TEXTFIELD));
	keyTextField->addEventListenerTextField(this, textfieldeventselector(CMainLayer::textFieldEvent));

	UIImageView * searchSprite = dynamic_cast<UIImageView*> (m_pUILayer->getWidgetByName(UI_SEARCH_SPRITE));
	//searchSprite->addTouchEventListener(this, toucheventselector(CMainLayer::searchImageViewtouchEventCallback));
	*/
	

	//------------- Word Scrollview ---------//
	m_pWordScrollViewLayer = CWordScrolllViewLayer::create(ui_layout.Word_Scrollviewer_BK_Color, ui_layout.Word_Show_Layer_Rect);
	m_pWordScrollViewLayer->setTag(ui_layout.TAG_WordScrollViewLayer);
	whole_layer->addChild(m_pWordScrollViewLayer); 
	
	//------------- Donation Scrollview ---------//
	m_pDonationScrollViewLayer= CWordScrolllViewLayer::create(ui_layout.Donation_Scrollviewer_BK_Color, ui_layout.Donation_Show_Layer_Rect);
	m_pDonationScrollViewLayer->setTag(ui_layout.TAG_DonationScrollViewLayer);
	whole_layer->addChild(m_pDonationScrollViewLayer);
	
	m_curScrollviewerLayerID = 0;	//default to show word scrollviewer layer;
	m_scrollViewerCount = 2;		//2 scrollviewer now;
		
	//test for word scrollviewer;
	vector<CWordItem>* wordItems = CWordManager::getInstance().GetWords("ابابیله");	
	if(wordItems)
	{	
		m_pWordScrollViewLayer->SetWordItemVectorToDisplay(wordItems, true);
	}	   
	//test for donation scrollviewer;
	ShowText(m_pDonationScrollViewLayer, "Donation:     test !!!!!");


	//for test;
	CCNotificationCenter::sharedNotificationCenter()->postNotification("WordScrollView_MSG", (CCObject*)this);

	//Enable this layer touch event;
	 setTouchEnabled(true);	

    return true;
}
/*
void CMainLayer::searchImageViewtouchEventCallback(CCObject *pSender, cocos2d::ui::TouchEventType eventType)
{
	switch (eventType)
	{
	case cocos2d::ui::TouchEventType::TOUCH_EVENT_ENDED:
		{
			UITextField *keyTextField = dynamic_cast<UITextField*> (m_pUILayer->getWidgetByName(UI_KEY_TEXTFIELD));
			string key = keyTextField->getStringValue();
			vector<string> wordStrings = CUIManager::getInstance().GetWordItemStrings(key);
		}
		break;
	default:
		break;
	}
}
*/
void CMainLayer::textFieldEvent(CCObject *pSender, TextFiledEventType type)
{
	switch (type)
	{
	case TEXTFIELD_EVENT_ATTACH_WITH_IME:
		{
			UITextField* textField = dynamic_cast<UITextField*>(pSender);

// 			if (strcmp(textField->getName(), "confirm_TextField") == 0)
// 			{
// 				CCMoveBy* moveBy = CCMoveBy::create(0.1f, ccp(0, textField->getContentSize().height * 2.5));
// 				m_pLayout->runAction(moveBy);
// 			}
			CCLog("点击");
		}
		break;

	case TEXTFIELD_EVENT_DETACH_WITH_IME:
		{
			UITextField* textField = dynamic_cast<UITextField*>(pSender);

// 			if (strcmp(textField->getName(), "confirm_TextField") == 0)
// 			{
// 				CCMoveBy* moveBy = CCMoveBy::create(0.1f, ccp(0, -textField->getContentSize().height * 2.5));
// 				m_pLayout->runAction(moveBy);
// 			}

			CCLog("移开");
			printf("%s",textField->getStringValue());
		}
		break;

	case TEXTFIELD_EVENT_INSERT_TEXT:
	case TEXTFIELD_EVENT_DELETE_BACKWARD:
		{
			bool bFindWord = false;

			CCLog("增加字段 in text field");
			UITextField* textField = dynamic_cast<UITextField*>(pSender);
			
			//check string is number
			string str = textField->getStringValue();

			//for test, 
			if(str == "0")
			{
				//test for word scrollviewer;
				vector<CWordItem>* wordItems = CWordManager::getInstance().GetWords("ابابیله");	
				if(wordItems)
				{	
					m_pWordScrollViewLayer->SetWordItemVectorToDisplay(wordItems, true);
				}
				break;
			}

			//else if string is number, random to choose one word to show;
			char * p ;
			strtol(textField->getStringValue(), &p, 10) ;
			bool isNumber = (*p == 0)?true:false ;

			if(isNumber)
			{				 
				map<string, vector<CWordItem> >* pWordMap = &(CWordManager::getInstance().m_wordsMap);
				int id = (int)rand()%(pWordMap->size());
				bFindWord = ShowWord(m_pWordScrollViewLayer, id); 
			}
			else
				bFindWord = ShowWord(m_pWordScrollViewLayer, textField->getStringValue());
// 			map<string, vector<CWordItem> >* pWordMap = &(CWordManager::getInstance().m_wordsMap);
// 			int index = (int)rand()%(pWordMap->size())+1;
// 			map<string, vector<CWordItem> >::iterator it = pWordMap->begin();
// 			std::advance(it, index);
// 			string thisKey = it->first;
// 			vector<CWordItem> wordItems = it->second;
// 			m_pWordScrollViewLayer->SetWordItemVectorToDisplay(&wordItems, true);
		}		
		break;

	default:
		break;
	}

}

void CMainLayer::sectionButtonsCallback(CCObject *pSender, TouchEventType type)
{

	UIButton *pButton = (UIButton*) pSender;

	CCLog(" section button event");
	switch(type)
	{
	case TOUCH_EVENT_BEGAN:
		break;

	case TOUCH_EVENT_MOVED:
		break;

	case TOUCH_EVENT_ENDED:
		SetButtonFocused(pButton);	//set section buttons focused
				
		//based on button selected, change scroll viewer to show;
		if(m_sectionWordbtn->isFocused())
		{
			ShowScrollviewer(0);
		}
		else if(m_sectionDonationbtn->isFocused())
		{
			ShowScrollviewer(1);
		}  		
		//CCLog("word layer: isTouchEnabled = %d, m_scrollview = %d  ", m_pWordScrollViewLayer->isTouchEnabled(), m_pWordScrollViewLayer->m_scrollView->isTouchEnabled());
		//CCLog("Donation layer: isTouchEnabled = %d, m_scrollview = %d  ", m_pDonationScrollViewLayer->isTouchEnabled(), m_pDonationScrollViewLayer->m_scrollView->isTouchEnabled())	;
		break;
	case TOUCH_EVENT_CANCELED:
		break;

	default:
		break;
	}
}

//based on current scrollviewer id to show one scrollviewer
void CMainLayer::ShowScrollviewer(int curLayerId)
{
// 	if(m_curScrollviewerLayerID == curLayerId)
// 		return;

	if(curLayerId < 0)
		curLayerId = 0;

	if(curLayerId >= m_scrollViewerCount)
		curLayerId = m_scrollViewerCount -1;

	float xOffset = -1 * curLayerId * m_pWordScrollViewLayer->getContentSize().width;	 //calculate x offset to move all layers;
	MoveScrollviewers(xOffset);	
	m_curScrollviewerLayerID = curLayerId;

	if(curLayerId == 0)
		SetButtonFocused(m_sectionWordbtn);
	else if	(curLayerId == 1)
		SetButtonFocused(m_sectionDonationbtn);
}


//************************************
// Method:    MoveScrollviewers
// FullName:  CMainLayer::MoveScrollviewers
// Access:    protected 
// Returns:   void
// Qualifier: based on x delta to move scrollviewer;
// Parameter: float xOffset : x Offset;
//************************************
void CMainLayer::MoveScrollviewers(float xOffset)
{		
	CUIManager::UI_LAYOUT ui_layout = CUIManager::getInstance().ui_layout;

	//new word scrollviewer position
	CCPoint newWordLayerPos = ccp(ui_layout.Word_Show_Layer_Rect.origin.x + xOffset, ui_layout.Word_Show_Layer_Rect.origin.y);
	m_pWordScrollViewLayer->setPosition(newWordLayerPos);

	//new donation scrollviewer position;
	CCPoint newDonationLayerPos = ccp(ui_layout.Donation_Show_Layer_Rect.origin.x + xOffset, ui_layout.Donation_Show_Layer_Rect.origin.y);
	m_pDonationScrollViewLayer->setPosition(newDonationLayerPos);
}


//set buttons focused;
void CMainLayer::SetButtonFocused(UIButton* pButton)
{
	//set all buttons not focused
	m_sectionDonationbtn->setFocused(false);
	m_sectionWordbtn->setFocused(false);

	//set this button focused;
	pButton->setFocused(true);
}

void CMainLayer::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}

bool CMainLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	bool bRet = true;  
	
	m_touchdownPos = pTouch->getLocation();

	return bRet;  
}

void CMainLayer::ccTouchMoved (CCTouch *pTouch, CCEvent *pEvent)
{
	//m_pWordScrollViewLayer->ccTouchMoved(pTouch, pEvent); 

	CCPoint curPos = pTouch->getLocation();
	float xOffset = curPos.x - m_touchdownPos.x;
	float currentLayerCenter =  (-1) * m_curScrollviewerLayerID * m_pWordScrollViewLayer->getContentSize().width;
	MoveScrollviewers(xOffset + currentLayerCenter);
}

void CMainLayer::ccTouchEnded (CCTouch *pTouch, CCEvent *pEvent)
{		   
	CCPoint curPos = pTouch->getLocation();
	float xOffset = curPos.x - m_touchdownPos.x;
	float xAbsOffset = fabsf(xOffset);
	float scrollviewWidth = m_pWordScrollViewLayer->getContentSize().width;
	float xScale = scrollviewWidth / 2;
	
	if(xAbsOffset>= xScale)	//if offset is more than half of scrollviewer width, then move to next one;
	{
		if(xOffset > 0)
		{
			ShowScrollviewer(m_curScrollviewerLayerID - 1);
		}
		else
		{
			ShowScrollviewer(m_curScrollviewerLayerID + 1);
		}
	}	 
	else
		ShowScrollviewer(m_curScrollviewerLayerID);
}

void CMainLayer::ccTouchCancelled (CCTouch *pTouch, CCEvent *pEvent)
{
		CCLog("Main layer: ccTouchCancelled");
}

//show word in scrollview layer
bool CMainLayer::ShowWord(CWordScrolllViewLayer* pScrollviewer, const char* term)
{
	map<string, vector<CWordItem> >* pWordMap = &(CWordManager::getInstance().m_wordsMap);
	map<string, vector<CWordItem> >::iterator it = pWordMap->find(term);
	if(it != pWordMap->end())
	{
		//find this key and show the result;
		vector<CWordItem> wordItems = it->second;
		pScrollviewer->SetWordItemVectorToDisplay(&wordItems, true);

		CCLog("Show words: key = %s", term);
		return true;
	}
	else
	{
		//can not find this key;
		string res = "Can not find words: ";
		res += term;
		ShowText(pScrollviewer, res.c_str());

		CCLog(res.c_str());
		return false;
	}
}

//show word in scrollview layer
bool CMainLayer::ShowWord(CWordScrolllViewLayer* pScrollviewer, int id)
{  
	map<string, vector<CWordItem> >* pWordMap = &(CWordManager::getInstance().m_wordsMap);
	if(pWordMap->size() <= 0)
		return false;

	map<string, vector<CWordItem> >::iterator it = pWordMap->begin();
	std::advance(it, id);
	string thisKey = it->first;
	vector<CWordItem> wordItems = it->second;
	// 			if(m_pWordScrollView)
	// 				delete m_pWordScrollView;
	pScrollviewer->SetWordItemVectorToDisplay(&wordItems, true);
	CCLog("Show words: id = %d", id);
	return true;
}

//show text in scrollview layer;
void CMainLayer::ShowText(CWordScrolllViewLayer* pScrollviewer, const char* str)
{
	pScrollviewer->SetTextToDisplay(str);
}