#pragma once
#ifndef _TOWER_PIN_
#define _TOWER_PIN_
#include "Tower.h"

class TowerPin :public Tower
{
protected:
	int const Id = 28;
	void Attack(float Delta);
	virtual bool Initiate();

public:
	CREATE_FUNC(TowerPin);
};
#endif _TOWER_PIN_
