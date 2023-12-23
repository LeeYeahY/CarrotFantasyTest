#ifndef _loadingScene_
#define _loadingScene_

#include "cocos2d.h"
using namespace cocos2d;

class GameScene;

class LoadingScene :public Scene
{
public:

    CREATE_FUNC(LoadingScene);

protected:

    virtual bool init()override;

    virtual void onEnter()override;

    virtual void onExit()override;

    virtual void sourceLoadCallBack(Ref* pData);

protected:

    GameScene* pGameScene = nullptr;

};

#endif 

