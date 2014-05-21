#include "main.h"
#include "AppDelegate.h"
#include "CCEGLView.h"
#include "../Classes/UI/UIManager.h"

USING_NS_CC;



/* list
http://en.wikipedia.org/wiki/List_of_displays_by_pixel_density
iPhone 3GS	3 / 3rd gen	8.9 (3.5)	320x480	64 (163)	3:2	1
iPhone 4 / iPod Touch	4 / 4th gen	8.9 (3.5)	960x640	128 (326)	3:2	2
iPhone 4S / iPod Touch	4S / 4th gen	8.9 (3.5)	960x640	128 (326)	3:2	2
iPhone 5 / iPod Touch	5 / 5th gen	10 (4)	1136x640	128 (326)	71:40 (~16:9)	2
iPhone 5C	5C / 5th gen	10 (4)	1136x640	128 (326)	71:40 (~16:9)	2
iPhone 5S	5S / 6th gen	10 (4)	1136x640	128 (326)	71:40 (~16:9)	2
*/

int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // create the application instance
    AppDelegate app;
    CCEGLView* eglView = CCEGLView::sharedOpenGLView();
    eglView->setViewName("PashtoDictionary");
    eglView->setFrameSize(IPHONE5_RESOLUTION);
    return CCApplication::sharedApplication()->run();
}
