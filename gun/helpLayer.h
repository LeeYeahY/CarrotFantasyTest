#ifndef _helpLayer_
#define _helpLayer_

#include "publicDefine.h"
#include "ui/CocosGUI.h"
using namespace ui;
//const static unsigned int THEME_PAGEVIEW_ARRAY[] = { 1, 2, 3, 4 };
class HelpLayer :public Layer
{
public:

    CREATE_FUNC(HelpLayer);

    virtual ~HelpLayer();

protected:

    virtual bool init()override;

    virtual void PageViewR();

private:
    Sprite* bottomSprite;

    int iCurLevelIndex = 0;

    PageView* pPageView = nullptr;

};

#endif 