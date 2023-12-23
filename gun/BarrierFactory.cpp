#include "BarrierFactory.h"
#include "BarrierBase.h"
BarrierBase* BarrierFactory::CreateBarrier(const BarrierType& MyBarrierType)
{
    //根据传入的障碍物类型初始化障碍物的指针
    BarrierBase* Barrier = nullptr;

    switch (MyBarrierType) {
    case BALLON:
        break;
    case CLOUD:
        break;
    case STONE:
        break;
    case TREE:
        break;
    default:
        break;
    }
    return Barrier;
}