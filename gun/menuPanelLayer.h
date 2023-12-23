#ifndef _menuPanelLayer_
#define _menuPanelLayer_

#include "publicDefine.h"

class PageViewLayer;

class MenuPanelLayer :public Layer
{
public:

    CREATE_FUNC(MenuPanelLayer);

    virtual void setPageTurnFunc(const std::function<void(const bool&)>& rFuncPageTurn);

protected:

    virtual bool init();

    virtual void createItemPanel();

private:

    std::function<void(const bool&)> funcPageTurn;

};


#endif 