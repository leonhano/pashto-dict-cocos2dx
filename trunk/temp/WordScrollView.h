#ifndef __cocos2d_x___CWordScrolllView_H__
#define __cocos2d_x___CWordScrolllView_H__

#include "cocos2d.h"

#include "cocos-ext.h"
#include "../DataStruct/WordItem.h"

using namespace cocos2d::extension;
using namespace cocos2d::ui;

USING_NS_CC;
using namespace std;

//this is a class which is same as CWordScrollViewLayer. 
//Only differernt: CWordScrollViewLayer is heritated from CCColorLayer;
class CWordScrolllView 
{
public:
	CWordScrolllView(CCRect rect, CCNode *container, CWordItem* pWordItem );
	virtual ~CWordScrolllView();
public:	
	//void SetParentContainer(CCNode *container);
	

	//set term font
	void SetTermFont(string termFontName);
									   	
	//event handle functions						
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
protected:
	CCScrollView* m_scrollView;
	CCLayerColor* m_container;	//container

	//Labels
	CCLabelTTF* m_termLabel;
	CCLabelTTF* m_pronunciationLabel;
	vector<CCLabelTTF*> m_meansLabels;
	vector<CCLabelTTF*> m_sampleSentencesLabels;

	//create LabelTTF;
	CCLabelTTF* CreateLabel (const string& str, const char *fontName, float fontSize, float height, const ccColor3B& color);

	//set wordItem to Display
	void SetWordItemToDisplay(CWordItem* pWordItem);

	void onMsgCenter(CCObject* obj);

	//add touch delegate;
	bool m_bIsTouchEnabled;				   
};
#endif