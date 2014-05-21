#include "HelloWorldScene.h"
#include "DataStruct\WordManager.h"

USING_NS_CC;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
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
                                        menu_selector(HelloWorld::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Arial", 24);
    
    // position the label on the center of the screen
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(pLabel, 1);

	/*
    // add "HelloWorld" splash screen"
    CCSprite* pSprite = CCSprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);
    */

	//Test();	//for test

    return true;
}


void HelloWorld::menuCloseCallback(CCObject* pSender)
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

void HelloWorld::AddLabel(CCString str, int xIndex, int yIndex)
{
	CCLabelTTF* pLabel = CCLabelTTF::create(str.getCString(), "Arial", 20);
	pLabel->setDimensions(CCSize(ccp(800, 50)));

	int x = 80 + xIndex * 250;
	int y = CCDirector::sharedDirector()->getVisibleSize().height - 70 - 40 *yIndex;
	pLabel->setPosition(ccp(x,y));

	this->addChild(pLabel, 1);
}

void HelloWorld::AddLabel(vector<string> strVector, int& xIndex, int yIndex)
{	
	string temp;
	for(vector<string>::iterator it = strVector.begin(); it!= strVector.end(); ++it)
	{
		//temp = temp + *it;
		AddLabel(*it, xIndex++, yIndex);
	}

	//CCString* label = CCString::createWithFormat("%s", temp.c_str());
	//AddLabel(temp, xIndex, yIndex);	
}

//------------------------test------------------
/*
void HelloWorld::Test()
{	
	TestAddWord();
	
	//std::cout << "------list all member------" << '\n';
	map<string, CWordItem> &words = CWordManager::getInstance().m_words;
	int yIndex = 0;
	// show content:
	for (std::map<string, CWordItem>::iterator it=words.begin(); it!=words.end(); ++it)
	{
		int xIndex = 0;
		//std::cout << it->first << " => " << it->second << '\n';
		CCString key = it->first;
		CWordItem word = it->second;
			
		AddLabel(key, xIndex++, yIndex);
		AddLabel(word.m_pronunciation, xIndex++, yIndex);
		AddLabel(word.m_means, xIndex, yIndex);

		if(word.m_sampleSentence.size() > 0)
		{
			AddLabel(word.m_sampleSentence, xIndex, yIndex);		
		}

		yIndex++;
	}

	TestManagerInsert(yIndex);
}

void HelloWorld::TestAddWord()
{
	int id = 0;	

	//add word1
	CWordItem wordItem1("ا", id++);
	wordItem1.AddPronunciation("Alif");
	wordItem1.AddMean("The first letter of the Pushto alphabet");
	CWordManager::getInstance().AddWord(wordItem1);

	//add word2
	vector<string> means2;
	means2.push_back("Dad, Daddy");
	means2.push_back("Ancestors");
	CWordManager::getInstance().AddWord("ابا", id++, "ābā", means2);
	
	//add word3
	CWordItem wordItem3("ابابیله", id++);
	wordItem3.AddMean("Abābīla");
	wordItem3.AddMean("A kind of swallow");
	wordItem3.AddSentence("Sample Sentence: Hello, how are you!!!");
	CWordManager::getInstance().AddWord(wordItem3); 															
} 

void HelloWorld::TestManagerInsert(int yIndex)
{
	int xIndex = 0;
	//insert a new mean;
	AddLabel("operation: Insert a new mean, print source text string: ", xIndex++, yIndex);
	CWordManager::getInstance().InsertMean("ا", "New!!! Insert mean");

	CWordItem* one = CWordManager::getInstance().GetWord("ا");
	if(one)
	{
		//CCLog(one->ToString().c_str());
		AddLabel(one->ToString(), xIndex+2, yIndex++);
	}
}
*/