#ifndef _gameSettingScene_
#define _gameSettingScene_

#include "publicDefine.h"

class GameSettingScene :public Scene
{
public:

    CREATE_FUNC(GameSettingScene);

    virtual ~GameSettingScene();

protected:

    virtual bool init();

    virtual void onEnter()override;

private:

    Layer* pPanelLayer = nullptr;
};

#endif
