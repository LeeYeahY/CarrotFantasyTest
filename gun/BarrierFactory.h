#pragma once
#ifndef _BARRIER_FACTORY_
#define _BARRIER_FACTORY_
#include "PublicDefine.h"
class BarrierBase;
class BarrierFactory 
{
public:
	static BarrierBase* CreateBarrier(const BarrierType& MyBarrierType);
};
#endif
