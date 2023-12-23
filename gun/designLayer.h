#ifndef _designLayer_
#define _designLayer_

#include "cocos2d.h"

using namespace cocos2d;

class DesignLayer : public Layer
{
public:

    CREATE_FUNC(DesignLayer);

protected:

    virtual bool init();

    virtual void loadSource();

};

#endif
