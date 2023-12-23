#pragma once
#ifndef _BARRIER_FACTORY_
#define _BARRIER_FACTOER_
#include "PublicDefine.h"
#include <functional>

class Entity;

class BarrierManager : public Ref
{
public:

    CREATE_INSTANCE_FUNC(BarrierManager);
    DESTROY_INSTANCE_FUNC();

    BarrierVec& GetBarrierVec();
    virtual void SetFuncAddBarrierToLayer(const std::function<void(Entity*)>& FuncAddBarrierToLayer);
    virtual void ClearBeAtkLockState();
    virtual void ClearManager();

protected:

    friend class BarrierBase;
    virtual void AddBarrier(BarrierBase* Barrier);
    virtual bool Initiate();
    virtual void RecordBarrierDeadEvent();
    virtual void RemoveBarrierFromManager(Ref* Barrier);

private:

    BarrierVec* MyBarrierVec = nullptr;
    std::function<void(Entity*)> AddBarrierToLayer;

    BarrierManager();
    virtual ~BarrierManager();
    BarrierManager(const BarrierManager&) = delete;
    BarrierManager& operator=(const BarrierManager&) = delete;
};
#endif
