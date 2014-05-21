#ifndef __MAINLAYER_H__
#define __MAINLAYER_H__

#include "cocos2d.h"   
#include "cocos-ext.h" 
#include "WordScrollViewLayer.h"

using namespace cocos2d::extension;
using namespace cocos2d::ui;

USING_NS_CC;
using namespace std;

class CMainLayer : public cocos2d::CCLayer
{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init(); 

	virtual void OnEnter();
	virtual void OnExit();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::CCScene* scene();
	
	//imageview callback
	//void searchImageViewtouchEventCallback(CCObject *pSender, cocos2d::ui::TouchEventType eventType);
	//text field callback
	void textFieldEvent(CCObject *pSender, TextFiledEventType type);
	// a selector callback
	void menuCloseCallback(CCObject* pSender);

	//section buttons call back;
	void sectionButtonsCallback(CCObject *pSender, TouchEventType type);

	//set button focused
	void SetButtonFocused(UIButton* pButton);

	// implement the "static node()" method manually
	CREATE_FUNC(CMainLayer);

private:
	TouchGroup* m_pUILayer; //layer对象
	//UILayout* m_pLayout;

	CWordScrolllViewLayer* m_pWordScrollViewLayer;		//scrollview layer
	CWordScrolllViewLayer* m_pDonationScrollViewLayer;		//scrollview layer
	UIButton* m_sectionWordbtn;							//section word button;
	UIButton* m_sectionDonationbtn;						//section Donation button;

protected :

	void ShowScrollviewer(int curLayerId);		//based on current scrollviewer id to show scrollviewer

public:	
	//show word
	bool ShowWord(CWordScrolllViewLayer* pScrollviewer, const char* term);	//show word in scrollview layer
	bool ShowWord(CWordScrolllViewLayer* pScrollviewer, int id);
	void ShowText(CWordScrolllViewLayer* pScrollviewer, const char* str);
};

#endif // __MAINLAYER_H__
