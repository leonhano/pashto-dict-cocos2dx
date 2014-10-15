#include "cocos2d.h"

#include "cocos-ext.h"
#include "../DataStruct/WordItem.h"

using namespace cocos2d::extension;
using namespace cocos2d::ui;

USING_NS_CC;
using namespace std;

//This is a layer for Home view
class CDonationViewLayer : public CCLayerColor
{		
public:
	//create function;
	static CDonationViewLayer* create(const ccColor4B& layerColor, const CCRect& rect);

	//overload from CCLayer;
	virtual bool initWithColor(const ccColor4B& layerColor, const CCRect& rect);

	
protected:
	CDonationViewLayer();	
	virtual ~CDonationViewLayer();

	void SetupUI(const CCRect& rect);
	 
	
};