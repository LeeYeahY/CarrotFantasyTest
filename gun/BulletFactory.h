#pragma once
#ifndef __Carrot__BarrierFactory__
#define __Carrot__BarrierFactory__
#include "PublicDefine.h"

class VictimEntityBase;

class BulletFactory
{
public:

	static BulletBase* CreateBullet(const int& BulletId, Tower* Tower, VictimEntityBase* VictimEntity);//�����ӵ�����
};

#endif