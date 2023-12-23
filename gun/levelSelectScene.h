#ifndef _levelSelectScene_
#define _levelSelectScene_

#include "sceneBase.h"

class LevelSelectScene : public SceneBase
{
public:

    CREATE_FUNC(LevelSelectScene);

    virtual ~LevelSelectScene();

protected:

    virtual bool init();

    virtual void onEnter()override;

private:

    int iThemeIndex = 0;

    Layer* pLevelSelectLayer = nullptr;
};

#endif
