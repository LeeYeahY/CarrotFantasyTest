#ifndef _helpMenuPanelLayer_
#define _helpMenuPanelLayer_

#include "publicDefine.h"

class HelpMenuPanelLayer :public Layer
{
public:

    CREATE_FUNC(HelpMenuPanelLayer);

protected:

    virtual bool init()override;

    virtual void createMenuPanel();

private:
    MenuItemToggle* pHelpBtn;
    MenuItemToggle* pMonsterHelpBtn;
    MenuItemToggle* pTowerHelpBtn;
    LayerMultiplex* pLayers = nullptr;
};

#endif
