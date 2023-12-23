#ifndef _pauseLayer_
#define _pauseLayer_

#include "publicDefine.h"

class PauseLayer :public Layer
{
public:

    CREATE_FUNC(PauseLayer);

    virtual void setFuncFlagPauseLayerIsClose(const std::function<void()>& rFuncFlagPauseLayerIsClose);

protected:

    virtual bool init();

    virtual void onEnter()override;

    virtual void onExit()override;

    virtual void createMenu();

    virtual void createSharedMenu();

    virtual void closeTouchEvent();

    std::function<void()> funcFlagPauseLayerIsClose;
};

#endif 
