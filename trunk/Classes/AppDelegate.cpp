#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "ui/UIManager.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include "tchar.h"
#endif

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {

    // create a scene. it's an autorelease object    
	//CCScene *pScene = CMainLayer::scene();
    //pDirector->runWithScene(pScene);

	/*
	int id = 0;	

	//add word1
	CWordItem wordItem1("ا", id++);
	wordItem1.AddPronunciation("Alif");
	wordItem1.AddMean("The first letter of the Pushto alphabet");
	CWordManager::getInstance().AddWord(&wordItem1);

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
	CWordManager::getInstance().AddWord(&wordItem3);
	*/

	CUIManager::getInstance().init();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	_tsetlocale(LC_ALL,_T(""));
	::AllocConsole();
	::freopen("conout$","w",stdout);
#endif

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

void AppDelegate::SetMultiResolution()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
	CCSize screenSize = pEGLView->getFrameSize();
	CCSize designSize = CCSizeMake(1024,614);
	pEGLView->setDesignResolutionSize(designSize.width,designSize.height, kResolutionExactFit);

	CCLog("Screen Size:%f %f",screenSize.width,screenSize.height);

	if(screenSize.height >= 320 && screenSize.height <= 480)
	{
		//android 1		800×480            5:3
		CCSize resourceSize = CCSizeMake(800, 480);
		pDirector->setContentScaleFactor(resourceSize.height/screenSize.height);
		CCLog("Resolution Scale OF Default =%f",resourceSize.height/screenSize.height);
	}
	else if(screenSize.height >= 540 && screenSize.height < 640 )
	{
		//android 4		960×540				16:9
		CCSize resourceSize = CCSizeMake(960, 540);
		pDirector->setContentScaleFactor(resourceSize.height/screenSize.height);
		CCLog("Resolution Scale OF Karboon=%f",resourceSize.height/screenSize.height);
	}
	else if( screenSize.height >= 640 && screenSize.height < 720 )

	{
		if(screenSize.width <= 960)
		{
			//iphone4		1136×640				16:9
			CCSize resourceSize = CCSizeMake(960, 640);  
			CCLog("Resolution Scale OF iphone4=%f",resourceSize.height/screenSize.height);	
			pDirector->setContentScaleFactor(resourceSize.height/screenSize.height);
		}
		else
		{		
			//iphone5		1136×640				16:9
			CCSize resourceSize = CCSizeMake(1136, 640);  
			CCLog("Resolution Scale OF iphone5=%f",resourceSize.height/screenSize.height);
			pDirector->setContentScaleFactor(resourceSize.height/screenSize.height);
		}
	}
	else if (screenSize.height >= 720 && screenSize.height < 768)
	{
		//android 3						 16:9
		CCSize resourceSize = CCSizeMake(1280, 720);
		pDirector->setContentScaleFactor(resourceSize.height/screenSize.height);
		CCLog("Resolution Scale OF NOTE=%f",resourceSize.height/screenSize.height);
	}
	else if (screenSize.height >= 768 && screenSize.height < 800)
	{	 
		//ipad1/ipad2/ipadmini		1024×768			4:3
		CCSize resourceSize = CCSizeMake(1024, 768);
		pDirector->setContentScaleFactor(resourceSize.height/screenSize.height);
		CCLog("Resolution Scale OF NOTE=%f",resourceSize.height/screenSize.height);

	}
	else if(screenSize.height > 800)
	{	
		//ipad3/ipad4		  2048×1536	  4:3
		CCSize resourceSize = CCSizeMake(2048, 1536);
		pDirector->setContentScaleFactor(resourceSize.height/screenSize.height);
		CCLog("Resolution Scale OF Nexus=%f",resourceSize.height/screenSize.height);
	}
	else
	{
		pDirector->setContentScaleFactor(1);
		CCLog("Resolution Scale OF S Advance=%f");
	}
}