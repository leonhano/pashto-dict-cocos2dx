#pragma once
#include "cocos2d.h"

#include "cocos-ext.h"

USING_NS_CC;
using namespace std;

class UITools
{
public:
	UITools(void) {};
	~UITools(void) {};

public:
	static CCLabelTTF* CreateLabel (const string& str, const char *fontName, float fontSize, const ccColor3B& color, float contentWidth);
};

