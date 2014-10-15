#include "UIManager.h"
#include "DataStruct/WordManager.h"
#include "MainLayer.h"

#include "cocos-ext.h"

using namespace cocos2d::extension;
using namespace cocos2d::ui;

void CUIManager::init()
{
	SetDevice(IPHONE5_RESOLUTION);	 //setup deveice
	SetUITheme();

	//add searchPath
	CCFileUtils::sharedFileUtils()->addSearchPath("Pashto_English_Data");
	CCFileUtils::sharedFileUtils()->addSearchPath("UI");

	//Test();

	//import data from csv file 
	CWordManager::getInstance().CreateWordsMapFromFile("part1.csv"); 
	// 	CWordManager::getInstance().CreateWordsMapFromFile("part2.csv");
	// 	CWordManager::getInstance().CreateWordsMapFromFile("part3.csv");
	// 	CWordManager::getInstance().CreateWordsMapFromFile("part4.csv");
	// 	CWordManager::getInstance().CreateWordsMapFromFile("part5.csv");
	// 	CWordManager::getInstance().CreateWordsMapFromFile("part6.csv");
	
	//run main layer;
	CCDirector* pDirector = CCDirector::sharedDirector();
	CCScene *pScene = CMainLayer::scene();
	pDirector->runWithScene(pScene);
}

void CUIManager::Test()
{		   
	//test to add words;
	TestAddWord();
		
	//hao - test for file reader;
	//FileReader::GetWordItemsFromFile("Pashto English Dictionary - Sheet1.tsv");

	// 	hao - test for file reader;
	// 		string str1 = wordItem1.TAGString();
	// 		FileReader::WriteStringsToFile(str1, "SourceData.txt", true);
	// 		string str3 = wordItem3.TAGString();
	// 		FileReader::WriteStringsToFile(str3, "SourceData.txt", true);
	
	/*
	CCSVParse* csvFile = new CCSVParse();
	csvFile->openFile("/Pashto_English_Data/part1.csv");  
	//csvFile->openFile("/Pashto_English_Data/Pashto English Dictionary - Sheet1.csv");  
	CCLog("---------- Begin to read Pashto English Dictionary - Sheet1 ----------");
	for (int i=0; i<csvFile->getRows(); ++i)  
	{  
		string strLine = "";  
		for(int j=0; j<csvFile->getCols(); ++j)  
		{  
			strLine += csvFile->getData(i,j);  
			strLine += ",";  
		}  
		CCLabelTTF* pLab = CCLabelTTF::create(strLine.c_str(),"Arial",20);  
		pLab->setColor(ccc3(255, 0, 0));  
		pLab->setPosition(ccp(size.width/2,size.height-150-i*30));  
		this->addChild(pLab,2);  
		CCLog(strLine.c_str());
	}  
	delete csvFile;
	*/

	CCLog("---------- End ----------");
}

void CUIManager::TestAddWord()
{	   
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
	wordItem3.AddMean("1Abābīla");
	wordItem3.AddMean("2A kind of swallow");
	wordItem3.AddMean("3Abābīla");
	wordItem3.AddMean("4A kind of swallow");
	wordItem3.AddMean("5Abābīla");
	wordItem3.AddMean("6A kind of swallow");
	wordItem3.AddMean("7Abābīla");
	wordItem3.AddMean("8A kind of swallow");
	wordItem3.AddMean("9Abābīla");
	wordItem3.AddMean("10A kind of swallow");
	wordItem3.AddMean("11Abābīla");
	wordItem3.AddMean("12A kind of swallow");
	wordItem3.AddMean("13Abābīla");
	wordItem3.AddMean("14A kind of swallow");
	wordItem3.AddMean("15Abābīla");
	wordItem3.AddMean("16A kind of swallow");
	wordItem3.AddSentence("1  Sample Sentence: Hello, how are you!!!");
	wordItem3.AddSentence("2  22222!!!");
	wordItem3.AddSentence("3333333!!");
	wordItem3.AddSentence("44444!!!");
	wordItem3.AddSentence("555555!!");
	wordItem3.AddSentence("666666!!");
	CWordManager::getInstance().AddWord(&wordItem3); 	  
} 

void CUIManager::ShowWord(string key)
{	
	/*
	vector<CWordItem>* wordsVector = CWordManager::getInstance().GetWords(key);
	if(wordsVector != NULL)
	{
		CWordItem wordItem = (*wordsVector)[0];
		string term = wordItem.m_term;
		//ShowTerm(term);
	}
	*/
}

vector<string> CUIManager::GetWordItemStrings(string key)
{
	vector<string> output;
	vector<CWordItem>* wordsVector = CWordManager::getInstance().GetWords(key);
	if(wordsVector != NULL)
	{
		for(vector<CWordItem>::iterator it=wordsVector->begin(); it!=wordsVector->end(); it++)
		{
			CWordItem& wordItem = *it;
			vector<string> wordItemString = wordItem.ToString();
			output.insert(output.end(), wordItemString.begin(), wordItemString.end());
		}
	}	

	return output;
}


//set device
void CUIManager::SetDevice(float width, float height)
{	
	// initialize director
	CCDirector* pDirector = CCDirector::sharedDirector();
	CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

	pDirector->setOpenGLView(pEGLView);

	//set multi screen;
	SetMultiResolution();
	CCSize designResolutionSize(width,height);
	pEGLView->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, kResolutionShowAll);

	// turn on display FPS
	pDirector->setDisplayStats(false);

	// set FPS. the default value is 1.0/60 if you don't call this
	pDirector->setAnimationInterval(1.0 / 60);
}

//set Multi Resolution;
void CUIManager::SetMultiResolution()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
	CCSize screenSize = pEGLView->getFrameSize();

	/*   original 		 
	CCSize designSize = CCSizeMake(screenSize.width,screenSize.height);
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
	*/
	/*   Portrait   */	  
	if(screenSize.width >= 320 && screenSize.width <= 480)
	{
		//android 1		800×480            5:3
		CCSize resourceSize = CCSize(480, 800);
		pDirector->setContentScaleFactor(resourceSize.height/screenSize.height);
		CCLog("Resolution Scale OF Default =%f",resourceSize.height/screenSize.height);
	}
	else if(screenSize.width >= 540 && screenSize.width < 640 )
	{
		//android 4		960×540				16:9
		CCSize resourceSize = CCSize(ANDROID4_RESOLUTION);
		pDirector->setContentScaleFactor(resourceSize.height/screenSize.height);
		CCLog("Resolution Scale OF Karboon=%f",resourceSize.height/screenSize.height);
	}
	else if( screenSize.width >= 640 && screenSize.width < 720 )

	{
		if(screenSize.height <=960)
		{
			//iphone4		1136×640				16:9
			CCSize resourceSize = CCSize(IPHONE4_RESOLUTION);  
			CCLog("Resolution Scale OF iphone4=%f",resourceSize.height/screenSize.height);	
			pDirector->setContentScaleFactor(resourceSize.height/screenSize.height);
		}
		else
		{		
			//iphone5		1136×640				16:9
			CCSize resourceSize = CCSize(IPHONE5_RESOLUTION);  
			CCLog("Resolution Scale OF iphone5=%f",resourceSize.height/screenSize.height);
			pDirector->setContentScaleFactor(resourceSize.height/screenSize.height);
		}
	}
	else if (screenSize.width >= 720 && screenSize.width < 768)
	{
		//android 3						 16:9
		CCSize resourceSize = CCSize(720, 1280);
		pDirector->setContentScaleFactor(resourceSize.height/screenSize.height);
		CCLog("Resolution Scale OF NOTE=%f",resourceSize.height/screenSize.height);
	}
	else if (screenSize.width >= 768 && screenSize.width < 800)
	{	 
		//ipad1/ipad2/ipadmini		1024×768			4:3
		CCSize resourceSize = CCSize(768, 1024);
		pDirector->setContentScaleFactor(resourceSize.height/screenSize.height);
		CCLog("Resolution Scale OF NOTE=%f",resourceSize.height/screenSize.height);

	}
	else if(screenSize.width > 800)
	{	
		//ipad3/ipad4		  2048×1536	  4:3
		CCSize resourceSize = CCSize(1536, 2048);
		pDirector->setContentScaleFactor(resourceSize.height/screenSize.height);
		CCLog("Resolution Scale OF Nexus=%f",resourceSize.height/screenSize.height);
	}
	else
	{
		pDirector->setContentScaleFactor(1);
		CCLog("Resolution Scale OF S Advance=%f");
	}
}
	
//set UI Theme
void CUIManager::SetUITheme()
{														
	CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
	CCSize screenSize = pEGLView->getFrameSize();

	CCLog("Test to use iphone5");
	//if(screenSize.equals(CCSize(IPHONE5_RESOLUTION)))
	{
		SetIphone5Layout();
	}
}

void CUIManager::SetIphone5Layout()
{
	//layout
	ui_layout.Whole_Layer_Size = CCSize(IPHONE5_RESOLUTION);
	
	int curY = ui_layout.Whole_Layer_Size.height;

	//background;
	curY -= 334;
	ui_layout.Bkg_Rect =  CCRect(0, curY, 638, 1150); 
	ui_layout.BKG_IMAGE1 = "background1.png";
	ui_layout.BKG_IMAGE2 = "background2.png";
	ui_layout.BKG_IMAGE3 = "background3.png";

	//Section areas
	curY = 1150 - 80;
	ui_layout.Section_Area_Rect = CCRect(0, curY, 640, 80);
	ui_layout.Section_Area_Bkg_Color =  ccc4f(192,192,192,180);
	ui_layout.Section_Button_FontName = "Arial";
	ui_layout.Section_Button_FontSize = 28;
	ui_layout.Section_Button_TextColor = ccWHITE;	
// 	ui_layout.Section_Button_Texture_Normal = "Section_Button_Normal.png";
// 	ui_layout.Section_Button_Texture_Selected = "Section_Button_Selected.png";
// 	ui_layout.Section_Button_Texture_Disabled = "Section_Button_Disabled.png";


	//Home button	
	ui_layout.Section_Home_Button_Rect = CCRect(70,curY +30 , 50, 50);
	//ui_layout.Section_Home_Button_Text = "Home";
	ui_layout.Section_Home_Button_Texture_Normal = "homeicon.png";
	ui_layout.Section_Home_Button_Texture_Selected = "highome.png";
	ui_layout.Section_Home_Button_Texture_Disabled = "homeicon.png";

	//word button
	ui_layout.Section_Word_Button_Rect = CCRect(296, curY +30, 50, 50);
	//ui_layout.Section_Word_Button_Text = "Word";
	ui_layout.Section_Word_Button_Texture_Normal = "deficon.png";
	ui_layout.Section_Word_Button_Texture_Selected = "highdefi.png";
	ui_layout.Section_Word_Button_Texture_Disabled = "deficon.png";

	//donation button
	ui_layout.Section_Donation_Button_Rect = CCRect(552, curY +30, 50, 50);
	//ui_layout.Section_Donation_Button_Text = "Donation";
	ui_layout.Section_Donation_Button_Texture_Normal = "donaicon.png";
	ui_layout.Section_Donation_Button_Texture_Selected = "highdona.png";
	ui_layout.Section_Donation_Button_Texture_Disabled = "donaicon.png";
	
	//key Textfield
	curY = 1150 - 465;
	ui_layout.Input_TextField_Rect = CCRect(45, curY + 58, 572, 65);
	ui_layout.IMG_TextField_Rect = CCRect(30, curY + 50, 572, 60);
	ui_layout.FONTSIZE_KEY_TEXTFIELD = 40;	//font size;
	ui_layout.FONTCOLOR_TEXTFIELD = ccc3(0.0f, 0.0f, 0.0f);

	//---------------------viewer---------------------------//
	ui_layout.LABEL_NORMAL_FONT_SIZE = 40;
	ui_layout.LABEL_TERM_FONT_SIZE = 40;
	ui_layout.LABEL_OTHER_FONT_SIZE = 30 ;
	ui_layout.LABEL_X_MARGIN = 10 ;
	ui_layout.LABEL_Y_MARGIN = 15;		
	ui_layout.LABEL_DEFAULT_TERM_FONTNAME = "Arial";
	ui_layout.LABEL_DEFAULT_OTHER_FONTNAME = "Pokhto" ;	

	//Home ScrollViewer
	ui_layout.Home_Show_Layer_Rect = CCRect(0, 0, 640, 700);
	ui_layout.Home_Scrollviewer_BK_Color = ccc4(192,192,192,180);//ccc4(73,107,155,180);

	//word ScrollViewer;
	ui_layout.Word_Show_Layer_Rect = CCRect(640, 0, 640, 700);
	ui_layout.Word_Scrollviewer_BK_Color = ccc4(192,192,192,180);//ccc4(173,207,255,180);

	//donation scrollviewer
	ui_layout.Donation_Show_Layer_Rect = CCRect(1280, 0, 640, 700);
	ui_layout.Donation_Scrollviewer_BK_Color = ccc4(192,192,192,180);//ccc4(255,107,200,180);	
}													 