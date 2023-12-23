#ifndef _tiledMapLayer_
#define _tiledMapLayer_

#include "cocos2d.h"
using namespace cocos2d;

class TiledMapLayer : public Layer
{
public:

    CREATE_FUNC(TiledMapLayer);

protected:

    virtual bool init();

    virtual void loadSource();

private:

    TMXTiledMap* pTiledMap = nullptr;
};

#endif
