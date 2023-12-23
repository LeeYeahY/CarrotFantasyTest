#pragma once
#ifndef _TOWER_FACTORY_
#define _TOWER_FACTORY_

#include "PublicDefine.h"

class Tower;

class TowerFactory
{
public:
    static Tower* CreateTower(const TowerType& MyTowerType, Vec2 Position);
};
#endif
