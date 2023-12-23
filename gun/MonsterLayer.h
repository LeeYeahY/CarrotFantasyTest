#pragma once
#ifndef __Carrot__MonsterLayer__
#define __Carrot__MonsterLayer__

#include "EntityLayerBase.h"

class MonsterBase;

/**
 *  monsterLayer use to show Monster
 */

class MonsterLayer :public EntityLayerBase
{
public:

    CREATE_FUNC(MonsterLayer);

protected:

    virtual bool init();

    virtual void RegisterMonsterDeadEvent();

    virtual void MonsterDead(Ref* Data);

    virtual void onExit()override;

};

#endif 