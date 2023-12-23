#ifndef _levelSelectLayer_
#define _levelSelectLayer_

#include "publicDefine.h"

class LevelSelectLayer : public Layer
{
public:

    CREATE_FUNC(LevelSelectLayer);

    virtual ~LevelSelectLayer();

protected:

    virtual bool init();

    virtual void loadSource();

    virtual void loadLevel();

    virtual void loadMenuItem();

    virtual std::tuple<int, bool> checkLevelIsLockAndBarrierIsClean(const int& rILevelIndex);

    virtual void changeToGameScene();

    virtual void loadData();


private:

    int iPageIndex = 0;

    int iCurLevelIndex = 0;

    ValueMap dataValueMap;

private:

    Sprite* pLockSprite = nullptr;

    MenuItemSprite* pStartBtn = nullptr;
};

#endif 

