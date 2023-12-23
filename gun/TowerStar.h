#pragma once
#include"Tower.h"
#ifndef _TOWER_STAR_
#define _TOWER_STAR_

class TowerStar :public Tower
{   
private:
	int const Id = 13;
	virtual bool Initiate();
	virtual void Attack(float Delta);

public:
	CREATE_FUNC(TowerStar);
};
#endif _TOWER_STAR_

