#ifndef __MainPageView_H__
#define __MainPageView_H__

#include "cocos2d.h"   
#include "cocos-ext.h" 

using namespace cocos2d::extension;
using namespace cocos2d::ui;

USING_NS_CC;

class CMainPageView : public UIPageView
{
public:
	static CMainPageView * 	create (CCRect pageviewRect);
protected:
	void onEnter();
	bool init(CCRect pageviewRect);

private:

};

#endif // __MainPageView_H__
