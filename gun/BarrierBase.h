#pragma once
#ifndef _BARRIER_BASE_
#define _BARRIER_BASE_
#include "VictimEntityBase.h"

class BarrierBase :public VictimEntityBase
{
public:

    static BarrierBase* Create(const int Id);
    friend class BarrierFactory;

protected:

    virtual bool Initiate(const int Id);
    virtual void DeadMove(const std::string& DeadImageFile = "");
    virtual void BeHurtAction();

};
#endif
