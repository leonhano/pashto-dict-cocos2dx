#ifndef __cocos2d_x___CUIManager_H__
#define __cocos2d_x___CUIManager_H__

//#include "MainLayer.h"
#include "cocos2d.h"  
USING_NS_CC;
using namespace std;

/* list
http://en.wikipedia.org/wiki/List_of_displays_by_pixel_density
iPhone 3GS	3 / 3rd gen	8.9 (3.5)	320x480	64 (163)	3:2	1
iPhone 4 / iPod Touch	4 / 4th gen	8.9 (3.5)	960x640	128 (326)	3:2	2
iPhone 4S / iPod Touch	4S / 4th gen	8.9 (3.5)	960x640	128 (326)	3:2	2
iPhone 5 / iPod Touch	5 / 5th gen	10 (4)	1136x640	128 (326)	71:40 (~16:9)	2
iPhone 5C	5C / 5th gen	10 (4)	1136x640	128 (326)	71:40 (~16:9)	2
iPhone 5S	5S / 6th gen	10 (4)	1136x640	128 (326)	71:40 (~16:9)	2
*/

#define ANDROID4_RESOLUTION		540,960//960,540
#define IPHONE4_RESOLUTION		640,960//960,640
#define IPHONE5_RESOLUTION		640,1136//1136,640

class CUIManager
{
public:
	static CUIManager &getInstance()
	{
		static CUIManager instance;
		return instance;
	}

private:
	CUIManager(){};
	// don't forget to declare these two. You want to make sure they
	// are unaccessible otherwise you may accidentally get copies of
	// your singleton appearing.
	CUIManager(CUIManager const&);		// Don't implement
	void operator=(CUIManager const&);	// Don't implement

private: 

public:
	/*
	enum Device
	{
		 ANDROID4 = 0,
		 IPHONE4,
		 IPHONE5
	};

	Device device;	 
	*/


	

	struct UI_LAYOUT
	{
		//UI Tags
		enum UITags {
			TAG_whole_layer			= 0,
			TAG_bk_Img				= 1,

			TAG_m_pUILayer			= 2,

			TAG_keyTextField_IMG	= 3,
			TAG_keyTextField		,

			TAG_sectionHomeBtn,
			TAG_sectionWordbtn,
			TAG_sectionDonationbtn,

			TAG_HomeScrollViewLayer,
			TAG_WordScrollViewLayer,
			TAG_DonationScrollViewLayer,
		};


		//Layout
		CCSize Whole_Layer_Size;

		//background img
		CCRect Bkg_Rect;
		const char* BKG_IMAGE1;		//backgournd image1
		const char* BKG_IMAGE2;		//background image2
		const char* BKG_IMAGE3;		//background image3

		//key Textfield
		CCRect Input_TextField_Rect;
		CCRect IMG_TextField_Rect;		 //background image for textField; 
		int FONTSIZE_KEY_TEXTFIELD;		//font size for key text fild
		ccColor3B FONTCOLOR_TEXTFIELD;	//font color;

		//Section Buttons
		CCRect Section_Area_Rect;
		ccColor4F Section_Area_Bkg_Color;
		const char* Section_Button_FontName;
		int Section_Button_FontSize;
		ccColor3B Section_Button_TextColor;	
// 		const char* Section_Button_Texture_Normal;
// 		const char* Section_Button_Texture_Selected;
// 		const char* Section_Button_Texture_Disabled;
		
		CCRect Section_Home_Button_Rect;			//Word Button
		//const char* Section_Home_Button_Text;
		const char* Section_Home_Button_Texture_Normal;
		const char* Section_Home_Button_Texture_Selected;
		const char* Section_Home_Button_Texture_Disabled;

		CCRect Section_Word_Button_Rect;			//Word Button
		//const char* Section_Word_Button_Text;
		const char* Section_Word_Button_Texture_Normal;
		const char* Section_Word_Button_Texture_Selected;
		const char* Section_Word_Button_Texture_Disabled;
		
		CCRect Section_Donation_Button_Rect;		//Donation Button
		//const char* Section_Donation_Button_Text;
		const char* Section_Donation_Button_Texture_Normal;
		const char* Section_Donation_Button_Texture_Selected;
		const char* Section_Donation_Button_Texture_Disabled;

		//---------------------viewer---------------------------//
		//All Labels in Scrollviewer
		int LABEL_NORMAL_FONT_SIZE;
		int LABEL_TERM_FONT_SIZE;
		string LABEL_DEFAULT_TERM_FONTNAME;
		int LABEL_OTHER_FONT_SIZE;
		string LABEL_DEFAULT_OTHER_FONTNAME;
		int LABEL_X_MARGIN;
		int LABEL_Y_MARGIN;

		//home scrollviewer
		CCRect Home_Show_Layer_Rect;
		ccColor4B Home_Scrollviewer_BK_Color;

		//word scrollviewer
		CCRect Word_Show_Layer_Rect; 
		ccColor4B Word_Scrollviewer_BK_Color;
		
		//donantion scrollviewer
		CCRect Donation_Show_Layer_Rect; 
		ccColor4B Donation_Scrollviewer_BK_Color;
	};
	UI_LAYOUT ui_layout;

	void init();

	void ShowWord(string key);
	vector<string> GetWordItemStrings(string key);

	void SetUITheme();
	void SetDevice(float width, float height);

protected:
	void SetMultiResolution();
	
	void SetIphone5Layout();

	//Hao todo: test need delete later;
	void TestAddWord();
	void Test();
};
#endif