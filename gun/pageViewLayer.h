#ifndef _pageViewLayer_
#define _pageViewLayer_

#include "publicDefine.h"
#include "ui/UIPageView.h"
using namespace ui;

class PageViewLayer : public Layer
{
public:

    virtual ~PageViewLayer();

    CREATE_FUNC(PageViewLayer);

    virtual void pageTurn(const bool& rBLeft);

protected:

    virtual bool init();

    virtual void setPageFlag(const int& rIIndex);

    virtual void createThemePageView();

    virtual void createThemeFlags();

    virtual void loadBg();

private:

    PageView* pPageView = nullptr;

    int iPageIndex = 0;

    Vector<MenuItemSprite*>* pPageFlagVec = nullptr;
};
#endif
