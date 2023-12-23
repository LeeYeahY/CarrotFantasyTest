#pragma once
#include"Tower.h"
#ifndef _TOWER_ROCKET_
#define _TOWER_ROCKET_
class TowerRocket :public Tower
{

	int const Id = 25;

	virtual bool Initiate();

	virtual void Attack(float Delta);

public:

	CREATE_FUNC(TowerRocket);
};
#endif _TOWER_ROCKET_
