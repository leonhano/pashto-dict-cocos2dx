#include "UITools.h"


//create label to add into this viewer;
CCLabelTTF* UITools::CreateLabel(const string& str, const char *fontName, float fontSize, const ccColor3B& color, float contentWidth)
{
	if(str.size() <= 0)
		return NULL;

	float height = ceil((str.length() * fontSize) / contentWidth) * ceil((float)(1.5) * fontSize );
	CCSize labelDimensions = CCSizeMake(contentWidth, height);

	CCLabelTTF* pLabel = CCLabelTTF::create(str.c_str(), fontName, fontSize, labelDimensions, kCCTextAlignmentLeft); 
	//CCLabelTTF* pLabel = CCLabelTTF::create(str.c_str(), fontName, fontSize); 
	pLabel->setAnchorPoint(ccp(0,0.5));
	pLabel->setContentSize(labelDimensions);
	
	//CCSize size = m_container->getContentSize();  
	//CCSize dimensions = CCSize(CCPoint(size.width, height))	;   
	//CCLog("CreateLabel() !!!!! weird , in andorid, can't use  setDimensions");
	//!!!!! weird , in andorid, can't use  setDimensions"!!!!!!
	//pLabel->setDimensions(dimensions);  

	pLabel->setColor(color);
	//pLabel->setHorizontalAlignment(kCCTextAlignmentLeft);  
	//CCLog("CreateLabel()");
	return pLabel;
}