#ifndef _welcomeScene_
#define _welcomeScene_

#include "PublicDefine.h"

class WelcomeScene :public Scene
{

public:

    CREATE_FUNC(WelcomeScene);

    virtual ~WelcomeScene();

protected:

    virtual bool init();

    virtual void onEnter()override;

    virtual void showMenu();

private:

    Layer* pSpritesLayer = nullptr;

    Layer* pMenusLayer = nullptr;

};

#endif