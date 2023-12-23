#ifndef _optionLayer_
#define _optionLayer_

#include "cocos2d.h"
using namespace cocos2d;

class OptionLayer :public Layer
{

public:

    CREATE_FUNC(OptionLayer);

protected:

    virtual bool init();

    virtual void loadSource();
};

#endif