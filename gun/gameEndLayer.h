#ifndef _gameEndLayer_
#define _gameEndLayer_

#include "publicDefine.h"

class GameEndLayer : public Layer
{

public:

    static GameEndLayer* create(const GameEndType& rEnGameEndType);

protected:

    virtual bool init(const GameEndType& rEnGameEndType);

    virtual void createMenu();

    virtual void loadInfo();

    virtual void onEnter()override;

    virtual void onExit()override;

    virtual void registerNoTouch();

    virtual void saveLevelData();

    virtual void playGameEndSound();

    virtual void checkCarrotType();

private:

    GameEndType enGameEndType = GameEndType(0);

    int iCarrotType = 0;

    std::string sCarrotType = "";

};

#endif
