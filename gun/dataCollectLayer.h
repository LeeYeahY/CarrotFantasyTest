#ifndef _dataCollectLayer_
#define _dataCollectLayer_

#include "cocos2d.h"

using namespace cocos2d;

class DataCollectLayer : public Layer
{
public:

    CREATE_FUNC(DataCollectLayer);

protected:

    virtual bool init();

    virtual void loadSource();

};

#endif
