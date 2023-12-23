#ifndef _pageSelectScene_
#define _pageSelectScene_

#include "publicDefine.h"


class PageSelectScene : public Scene
{
public:

    CREATE_FUNC(PageSelectScene);

    virtual ~PageSelectScene();

protected:

    virtual bool init();

    virtual void onEnter()override;

private:

    Layer* pPageViewLayer = nullptr;

    Layer* pMenuPanelLayerR = nullptr;

    Layer* pPageTurningLayer = nullptr;

};

#endif
