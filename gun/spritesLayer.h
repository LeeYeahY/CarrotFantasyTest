#ifndef _spritesLayer_
#define _spritesLayer_

#include "publicDefine.h"

class SpritesLayer : public Layer
{
public:

    CREATE_FUNC(SpritesLayer);

    virtual ~SpritesLayer();

protected:

    virtual bool init();

    virtual void createStaticSprites();

    virtual void createDynamicSprites();

    virtual void createCarrot();

    virtual void leafAction(float dt);

private:

    Node* pCarrotAll = nullptr;

    const Size visibleSize = Director::getInstance()->getVisibleSize();

};


#endif
