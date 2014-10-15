
#include "cocos2d.h"

#include "cocos-ext.h"
#include "../DataStruct/WordItem.h"

using namespace cocos2d::extension;
using namespace cocos2d::ui;

USING_NS_CC;
using namespace std;

//This is a layer, same as WordScrollView;
//Only differernt: CWordScrollViewLayer is heritated from CCColorLayer;
class CWordScrolllViewLayer : public CCLayerColor
{		
public:
	//create function;
	static CWordScrolllViewLayer* create(const ccColor4B &color, const CCRect& rect);
	static CWordScrolllViewLayer* create(const ccColor4B& layerColor, const CCRect& rect, 
										 const char* termFontName, const char* otherFontName);

	//overload from CCLayer;
	virtual bool initWithColor(const ccColor4B& layerColor, const CCRect& rect, 
								const char* termFontName, const char* otherFontName);

	//set wordItem to Display
	void SetWordItemToDisplay(CWordItem* pWordItem, bool removeAllOldItems);
	void SetWordItemVectorToDisplay(vector<CWordItem>* pWordItems, bool removeAllOldItems);
	void SetTextToDisplay(const char* str);

	//set term font
	//void SetTermFont(string termFontName);

	void CleanAll();
	
	//event handle functions
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

protected:
	CWordScrolllViewLayer();	
	virtual ~CWordScrolllViewLayer();

	float m_totalItemsHeight;
	ccColor4B m_layerColor;
	string m_termFontName;
	string m_otherFontName;
public:
	CCScrollView* m_scrollView;
	CCLayerColor* m_container;	//container

	CCLayer* m_parentLayer;	//for cast touch msg from this layer to main layer;

	//Labels
// 	vector<CCLabelTTF*> m_termLabels;
// 	vector<CCLabelTTF*> m_pronunciationLabels;
// 	vector<CCLabelTTF*> m_meansLabels;
// 	vector<CCLabelTTF*> m_sampleSentencesLabels;

	//create scrollview in this layer
	void CreateScrollView(const CCSize& size);
		
	//recreate all items
	void RecreateAllItems();

	//msg center;
	void onMsgCenter(CCObject* obj);
		   
};