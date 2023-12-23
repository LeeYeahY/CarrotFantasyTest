#ifndef _sharedMenu_
#define _sharedMenu_

#include "cocos2d.h"
using namespace cocos2d;

class SharedMenu : public Node
{
public:

    CREATE_FUNC(SharedMenu);

protected:

    virtual bool init();

    virtual void createMenu();
};

#endif
