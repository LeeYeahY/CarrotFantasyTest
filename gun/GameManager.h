#ifndef _gameManager_
#define _gameManager_

#include "PublicDefine.h"

class GameManager :public Ref
{
public:

    CREATE_INSTANCE_FUNC(GameManager);

    DESTROY_INSTANCE_FUNC();

protected:

    virtual bool Init();

    CC_SYNTHESIZE_PASS_BY_REF(int, myCarrotHp, MyCarrotHp);

    CC_SYNTHESIZE_PASS_BY_REF(int, myMonsterBatch, MyMonsterBatch);

    CC_SYNTHESIZE_PASS_BY_REF(bool, myIsPause, MyIsPause);

private:

    GameManager() {}

    GameManager(const GameManager&) = delete;

    GameManager& operator=(const GameManager&) = delete;

};

#endif
