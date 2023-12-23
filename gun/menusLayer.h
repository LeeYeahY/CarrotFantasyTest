#ifndef _menusLayer_
#define _menusLayer_

#include "publicDefine.h"

class MenusLayer :public Layer
{
public:

    CREATE_FUNC(MenusLayer);

protected:

    virtual bool init();

    virtual void createMenuItems();
};

#endif 
