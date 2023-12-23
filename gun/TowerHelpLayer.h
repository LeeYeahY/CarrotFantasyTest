#pragma once
#ifndef _TOWER_HELP_LAYER_
#define _TOWER_HELP_LAYER_
#include<string>
class TowerHelpLayer:public Layer
{
public:

    CREATE_FUNC(TowerHelpLayer);

    virtual ~TowerHelpLayer();

protected:

    virtual bool Initiate();

    virtual void PPageView();

private:

    PageView* MyPageView = nullptr;

    Sprite* BottomSprite;

    int CurLevelIndex = 0;
};
#endif _TOWER_HELP_LAYER_