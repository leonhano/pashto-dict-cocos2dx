
#include "DonationViewlayer.h" 
#include "UIManager.h"
#include "UITools.h"
#include "DataStruct/WordManager.h"

CDonationViewLayer::CDonationViewLayer()
{
	//m_parentLayer = NULL;


}

CDonationViewLayer::~CDonationViewLayer()
{
}

CDonationViewLayer * CDonationViewLayer::create(const ccColor4B& layerColor, const CCRect& rect)
{	
	CDonationViewLayer * pLayer = new CDonationViewLayer();
	if( pLayer && pLayer->initWithColor(layerColor, rect))
	{
		pLayer->setPosition(ccp(rect.getMinX(), rect.getMinY()));
		pLayer->autorelease();
		return pLayer;
	}
	CC_SAFE_DELETE(pLayer);
	return NULL;
}; 

bool CDonationViewLayer::initWithColor(const ccColor4B& layerColor, const CCRect& rect)
{
	if (!CCLayer::init())
	{
		return false;
	}

	float width = rect.size.width;
	float height = rect.size.height;
	//base layer is invisiable, no color;
	if(!CCLayerColor::initWithColor(layerColor, width, height))
	{
		return false;
	}
	this->setAnchorPoint(ccp(1,0));

	//enable touch event
	setTouchEnabled(true);
	  
	///set up UI;
	SetupUI(rect);
	return true;
}

//************************************
// Method:    SetupUI
// FullName:  CDonationViewLayer::SetupUI
// Access:    protected 
// Returns:   void
// Qualifier: setup UI
// Parameter: const CCRect & rect   : whole 
// Parameter: const char * termFontName   :
// Parameter: const char * otherFontName   :
// Parameter: int maxMeansLabel   :
//************************************
void CDonationViewLayer::SetupUI(const CCRect& rect)
{
	CUIManager::UI_LAYOUT ui_layout = CUIManager::getInstance().ui_layout;	
	//static label
	float labelWidth = this->getContentSize().width - ui_layout.LABEL_X_MARGIN;
	CCLabelTTF* pLabel = UITools::CreateLabel("Donation View", ui_layout.LABEL_DEFAULT_TERM_FONTNAME.c_str(), ui_layout.LABEL_NORMAL_FONT_SIZE, ccBLUE, labelWidth);	
	
	float curY = rect.size.height - (1.5 *ui_layout.LABEL_Y_MARGIN);
	pLabel->setPosition(ccp(ui_layout.LABEL_X_MARGIN, curY));	

	this->addChild(pLabel);
}
  