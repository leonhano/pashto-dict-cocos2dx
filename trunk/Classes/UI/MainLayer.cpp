#include "MainLayer.h"
#include "CocoStudio\GUI\UIWidgets\UITextField.h"
#include "UIManager.h"
#include "GUI\CCScrollView\CCScrollView.h"
#include "ccTypes.h"
#include "CocoStudio\GUI\BaseClasses\UIWidget.h"
#include "DataStruct\WordManager.h"

const int HomeID = 0;
const int WordID = 1;
const int DonationID = 2;

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
	
	//load all background images;
	m_pBkgTexture1 = CCTextureCache::sharedTextureCache()->addImage(ui_layout.BKG_IMAGE1);
	m_pBkgTexture2 = CCTextureCache::sharedTextureCache()->addImage(ui_layout.BKG_IMAGE2);
	m_pBkgTexture3 = CCTextureCache::sharedTextureCache()->addImage(ui_layout.BKG_IMAGE3);

	//------------whole layer---------------//
	//background image;
	m_pBkgSpirte = CCSprite::createWithTexture(m_pBkgTexture1);
	m_pBkgSpirte->setTag(ui_layout.TAG_whole_layer);
	m_pBkgSpirte->setAnchorPoint(CCPointZero);
	m_pBkgSpirte->setPosition(CCPointZero);
	this->addChild(m_pBkgSpirte, 0);	 

	// 	//text field image
	CCSprite* textfield_Img = CCSprite::create("Key_TextField.png");
	textfield_Img->setTag(ui_layout.TAG_keyTextField_IMG);
	textfield_Img->setAnchorPoint(CCPointZero);
	textfield_Img->setPosition(ui_layout.IMG_TextField_Rect.origin);
	m_pBkgSpirte->addChild(textfield_Img, 2);

	//------------- UI layer ------------//
	m_pUILayer = UILayer::create();
	m_pUILayer->setTag(ui_layout.TAG_m_pUILayer);
	m_pUILayer->scheduleUpdate();
	addChild(m_pUILayer, 5);

	//-------------create section layer --------------//
	CCLayerColor* sectionColorLayer = CCLayerColor::create(ccc4BFromccc4F(ui_layout.Section_Area_Bkg_Color), ui_layout.Section_Area_Rect.size.width, ui_layout.Section_Area_Rect.size.height);
	sectionColorLayer->setContentSize(ui_layout.Section_Area_Rect.size);
	sectionColorLayer->setPosition(ui_layout.Section_Area_Rect.origin);
	m_pBkgSpirte->addChild(sectionColorLayer, 2);			

	//--------create section buttons--------//
	//Home btn
	m_sectionHomebtn = AddButton(ui_layout.TAG_sectionHomeBtn,
		ui_layout.Section_Home_Button_Texture_Normal, ui_layout.Section_Home_Button_Texture_Selected, ui_layout.Section_Home_Button_Texture_Disabled,
		ui_layout.Section_Home_Button_Rect, true);

	//word btn
	m_sectionWordbtn =  AddButton(ui_layout.TAG_sectionWordbtn,
		ui_layout.Section_Word_Button_Texture_Normal, ui_layout.Section_Word_Button_Texture_Selected, ui_layout.Section_Word_Button_Texture_Disabled,
		ui_layout.Section_Word_Button_Rect, false); 

	//donation btn
	m_sectionDonationbtn =  AddButton(ui_layout.TAG_sectionDonationbtn,
		ui_layout.Section_Donation_Button_Texture_Normal, ui_layout.Section_Donation_Button_Texture_Selected, ui_layout.Section_Donation_Button_Texture_Disabled,
		ui_layout.Section_Donation_Button_Rect, false); 

	//-------- Create the textfield --------
	UITextField* keyTextField = UITextField::create(); 
	keyTextField->setTag(ui_layout.TAG_keyTextField);
	keyTextField->setMaxLengthEnabled(true); 
	keyTextField->setMaxLength(20);
	keyTextField->setTouchEnabled(true);
	keyTextField->setFontName("Arial");
	keyTextField->setFontSize(ui_layout.FONTSIZE_KEY_TEXTFIELD);
	keyTextField->setPlaceHolder("input words here");
	keyTextField->setColor(ui_layout.FONTCOLOR_TEXTFIELD);
	keyTextField->setAnchorPoint(CCPointZero);
	keyTextField->setPosition(ui_layout.Input_TextField_Rect.origin);
	keyTextField->setTouchSize(ui_layout.Input_TextField_Rect.size);
	keyTextField->setTouchAreaEnabled(true);
	keyTextField->setTextHorizontalAlignment(kCCTextAlignmentRight);
	keyTextField->addEventListenerTextField(this, textfieldeventselector(CMainLayer::textFieldEvent));
	m_pUILayer->addWidget(keyTextField);	
	
	//------------- Home Scrollview ---------//
	m_pHomeScrollViewLayer = CHomeViewLayer::create(ui_layout.Home_Scrollviewer_BK_Color, ui_layout.Home_Show_Layer_Rect);
	m_pHomeScrollViewLayer->setTag(ui_layout.TAG_HomeScrollViewLayer);
	m_pBkgSpirte->addChild(m_pHomeScrollViewLayer, 6); 
	
	//------------- Word Scrollview ---------//
	m_pWordScrollViewLayer = CWordScrolllViewLayer::create(ui_layout.Word_Scrollviewer_BK_Color, ui_layout.Word_Show_Layer_Rect);
	m_pWordScrollViewLayer->setTag(ui_layout.TAG_WordScrollViewLayer);
	m_pBkgSpirte->addChild(m_pWordScrollViewLayer, 6); 
	
	//------------- Donation Scrollview ---------//
	m_pDonationScrollViewLayer= CDonationViewLayer::create(ui_layout.Donation_Scrollviewer_BK_Color, ui_layout.Donation_Show_Layer_Rect);
	m_pDonationScrollViewLayer->setTag(ui_layout.TAG_DonationScrollViewLayer);
	m_pBkgSpirte->addChild(m_pDonationScrollViewLayer, 6);
	
	m_curScrollviewerLayerID = HomeID;	//default to show Home scrollviewer layer;
	m_scrollViewerCount = 3;		//3 scrollviewer now;

	//test for word scrollviewer;
	vector<CWordItem>* wordItems = CWordManager::getInstance().GetWords("ابابیله");	
	if(wordItems)
	{	
		m_pWordScrollViewLayer->SetWordItemVectorToDisplay(wordItems, true);
	}	   


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
			CCLog("text field: click");
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

			CCLog("text field: remove   ");
			printf("%s",textField->getStringValue());
		}
		break;

	case TEXTFIELD_EVENT_INSERT_TEXT:
	case TEXTFIELD_EVENT_DELETE_BACKWARD:
		{
			//when input text to search, viewer is not words, then move it to this viewer;
			if(!m_sectionWordbtn->isFocused())
			{
				SetButtonFocused(m_sectionWordbtn);	//set section buttons focused
				ShowScrollviewer(WordID);
			}
			bool bFindWord = false;

			CCLog("text field:  add");
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
		if(m_sectionHomebtn->isFocused())
		{
			ShowScrollviewer(HomeID);
		}
		else if(m_sectionWordbtn->isFocused())
		{
			ShowScrollviewer(WordID);
		}
		else if(m_sectionDonationbtn->isFocused())
		{
			ShowScrollviewer(DonationID);
		}  		
		else
			ShowScrollviewer(HomeID);
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
		curLayerId = HomeID;

	if(curLayerId >= m_scrollViewerCount)
		curLayerId = m_scrollViewerCount -1;
	
	ChangeBkgImage(curLayerId);

	float xOffset = -1 * curLayerId * m_pWordScrollViewLayer->getContentSize().width;	 //calculate x offset to move all layers;
	MoveScrollviewers(xOffset);	
	m_curScrollviewerLayerID = curLayerId;

	if(curLayerId == WordID)
		SetButtonFocused(m_sectionWordbtn);
	else if	(curLayerId == DonationID)
		SetButtonFocused(m_sectionDonationbtn);
	else
		SetButtonFocused(m_sectionHomebtn);
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

	//new home scrollviewer position
	CCPoint newHomeLayerPos = ccp(ui_layout.Home_Show_Layer_Rect.origin.x + xOffset, ui_layout.Home_Show_Layer_Rect.origin.y);
	m_pHomeScrollViewLayer->setPosition(newHomeLayerPos);

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
	m_sectionHomebtn->setFocused(false);
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


//************************************
// FullName:  CMainLayer::AddButton
// Qualifier: Add button into section area;
// Parameter: int tag   : tag
// Parameter: const char * normal   : normal texture file name
// Parameter: const char * selected   : selected texture file name
// Parameter: const char * disabled   : disable texture file name
// Parameter: const CCRect & rect   : rect
// Parameter: bool focused   : focused or not;
//************************************
UIButton* CMainLayer::AddButton(int tag, 
								const char* normal,const char* selected,const char* disabled, 
								const CCRect& rect, bool focused)
{
	UIButton* pbutton = UIButton::create();
	pbutton->setTag(tag);
	pbutton->loadTextures(normal, selected, disabled);
	//pbutton->setColor(ui_layout.Section_Area_Bkg_Color);
	//pbutton->setTitleFontName(ui_layout.Section_Button_FontName);
	//pbutton->setTitleFontSize(ui_layout.Section_Button_FontSize);
	//pbutton->setTitleColor(ui_layout.Section_Button_TextColor);
	//pbutton->setTitleText(ui_layout.Section_Home_Button_Text);
	pbutton->setPosition(rect.origin);
	pbutton->setSize(rect.size);
	pbutton->setVisible(true);
	pbutton->setTouchEnabled(true);
	pbutton->setFocused(focused);
	pbutton->addTouchEventListener(this, toucheventselector(CMainLayer::sectionButtonsCallback));
	m_pUILayer->addWidget(pbutton);
	return pbutton;
}

//************************************
// FullName:  CMainLayer::ChangeBkgImage
// Qualifier: Change background image;
// Parameter: int curLayerId   : current Id
//************************************
void CMainLayer::ChangeBkgImage(int curLayerId)
{
	if(curLayerId == DonationID)
	{
		m_pBkgSpirte->setTexture(m_pBkgTexture3);
	}
	else if(curLayerId == WordID)
	{
		m_pBkgSpirte->setTexture(m_pBkgTexture2);
	}
	else
	{
		m_pBkgSpirte->setTexture(m_pBkgTexture1);
	}
}